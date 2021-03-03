import argparse
import dateutil.parser
import itertools
import logging
import os
import subprocess
import sys

ARGPARSER = argparse.ArgumentParser()
ARGPARSER.add_argument('-d', '--deadline', dest='deadline', action='store', metavar='YYYY-MM-DDTHH:MM:SS+HH:MM',
                       help='Date and time at which the submissions are expected.')
ARGPARSER.add_argument('-l', '--show-log', dest='show_log', action='store_true',
                       help='Print git log of repositories.')
ARGPARSER.add_argument('-r', '--repo', dest='repo', action='store',
                       help='Specify a single repo rather than use depots.txt.')
ARGPARSER.add_argument('-m', '--moss-id', dest='mossid', action='store',
                       help='MOSS identifier. (See http://theory.stanford.edu/~aiken/moss/ to obtain an identifier.)')
ARGPARSER.add_argument('-o', '--show-output', dest='show_output', action='store_true',
                       help='Prints to screen the output of the programs evaluated.')
ARGPARSER.add_argument('-v', '--valgrind', dest='valgrind', action='store_true',
                       help='Run valgrind on program and show its output.')
ARGS = ARGPARSER.parse_args()

# Verify timestamp format, if present.
if ARGS.deadline:
    try:
        dateutil.parser.parse(ARGS.deadline)
    except ValueError:
        print('Bad deadline timestamp', sys.exc_info())
        sys.exit(100)

subprocess.run('gcc -g -c ../main.c -o main.o', shell=True)

def evaluate_repo(name, deadline=None):
    """Clone, compile and run tests on the given repo."""
    try:
        # Craft URL to clone given a depot name.
        remote_depot_name = name
        remote_depot_url = 'git@github.com:' + remote_depot_name + '.git'
        local_depot_path = remote_depot_name.replace('/', '-')
        print('=' * 10 + '\n' + local_depot_path)

        # Clone the repo.
        if (not os.path.exists(local_depot_path)):
            subprocess.run('git clone ' + remote_depot_url + ' ' + local_depot_path,
                           check=True, shell=True, text=True, stderr=subprocess.PIPE)

        # If timestamp is specified, checkout at that point in time.
        deadline = deadline or ARGS.deadline
        if deadline is not None:

            # rev_list_cmd = subprocess.run('git rev-list -n 1 --before="' + timestamp + '" master', 
            #                               cwd=local_depot_path, shell=True, capture_output=True, text=True, check=True)
            # if not rev_list_cmd.stdout:
            #     raise RuntimeError('repo non-existant at timestamp: ' + timestamp)

            # subprocess.run(['git checkout ' + rev_list_cmd.stdout], cwd=local_depot_path, shell=True, check=True, stderr=subprocess.PIPE)

            # Get time of last time commit and, if later than specified timestamp, mention it.
            last_commit_timestamp_cmd = subprocess.run('git log -1 --format=%cd --date=iso',
                                                       cwd=local_depot_path, capture_output=True, shell=True, text=True)

            last_commit_timestamp = dateutil.parser.parse(last_commit_timestamp_cmd.stdout)
            deadline_timestamp = dateutil.parser.parse(deadline)
            if(last_commit_timestamp > deadline_timestamp):
                try:
                    import termcolor
                    termcolor.cprint("Late submission by {}".format(last_commit_timestamp - deadline_timestamp), 'red', attrs=['blink'])
                    termcolor.cprint("Last commit: {}".format(last_commit_timestamp), 'red')
                except ImportError:
                    print("*** LATE SUBMISSION BY ", last_commit_timestamp - deadline_timestamp, " ***")
                    print("*** LAST COMMIT: ", last_commit_timestamp, " ***")

        # Show git log if requested.
        if ARGS.show_log:
            subprocess.run('git --no-pager log --all --decorate --graph --pretty=format:"%aD (%an) %s"', cwd=local_depot_path, shell=True)
            print('\n')

        # Compile liste.c and link with main.o.
        subprocess.run('gcc --debug -I ../.. -c liste.c -o liste.o', cwd=local_depot_path, shell=True, check=True, stderr=subprocess.PIPE, text=True)
        subprocess.run('gcc --debug ../main.o liste.o -o a.out', cwd=local_depot_path, shell=True, check=True, stderr=subprocess.PIPE, text=True)

        # Launch tested program.
        run_program_cmd = subprocess.run('./a.out', cwd=local_depot_path, shell=True, capture_output=True, text=True, timeout=3)
        if run_program_cmd.returncode != 0:
            print("Program returned error code: [" + str(run_program_cmd.returncode) + "]")

        # Show results.
        if ARGS.show_output:
            print(run_program_cmd.stdout)
        else:
            print("\n".join(run_program_cmd.stdout.splitlines()[-3:]))

        # Show valgrind analysis if requested.
        if ARGS.valgrind:
            subprocess.run('valgrind --log-fd=2 --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out 1>/dev/null',
                           cwd=local_depot_path, shell=True)

    except subprocess.CalledProcessError as e:
        print("Command \"" + e.cmd + "\" failed with error: [" + str(e.returncode) + "]" + e.stderr)
    except subprocess.TimeoutExpired as e:
        print("Command \"" + e.cmd + "\" timed out.")
    except RuntimeError as e:
        print("Failure: " + "\n".join(e.args))

if __name__ == "__main__":
    if sys.version_info < (3, 7, 5) and sys.platform == "linux":
        print("This script requires Python 3.7.5 or above due to a bug in subprocess' timeout handling.") # https://bugs.python.org/issue37424
        sys.exit(-2)

    if ARGS.repo is not None:
        evaluate_repo(ARGS.repo, ARGS.timestamp)
    else:
        with open('depots.txt') as depots_lines:
            for depots_line in itertools.dropwhile(lambda line: line.startswith('#'),
                                                   depots_lines):
                try:
                    cells = depots_line.rstrip().split(",")

                    # Parse the timestamp for that repo if it is specified.
                    timestamp = None
                    if len(cells) > 1:
                        try:
                            dateutil.parser.parse(cells[1])
                            timestamp = cells[1]
                        except:
                            raise RuntimeError('-1 bad timestamp format')

                    evaluate_repo(cells[0], timestamp)
                except RuntimeError as error:
                    print(error.args[0])

    # Submit files to MOSS service if requested.
    if ARGS.mossid:
        print('\n' + '=' * 3 + 'Submitting to MOSS' + '=' * 3)
        try:
            import mosspy
            import shutil, webbrowser

            moss = mosspy.Moss(ARGS.mossid, 'c')
            moss.setIgnoreLimit(3)
            moss.addBaseFile('../liste.c')
            moss.addFilesByWildcard('./**/liste.c')
            url = moss.send()
            print(url)
            if os.path.exists('moss/'):
                shutil.rmtree('moss/')
            mosspy.download_report(url, 'moss/', log_level=logging.ERROR)
        except ImportError as ie:
            print('Could not find MOSS module. Install it with \'$ pip3 install mosspy\'')
        except BaseException as be:
            print('MOSS submission error.', be.args)
        else:
            webbrowser.open('file://' + os.path.realpath('moss/index.html'))
