import argparse
import datetime
import itertools
import logging
import os
import subprocess
import sys

ARGPARSER = argparse.ArgumentParser()
ARGPARSER.add_argument('-t', '--timestamp', dest='timestamp', action='store', metavar='TIMESTAMP(DD-MM-YYY HH24:MM)',
                       help='Date and time at which to clone the repositories.')
ARGPARSER.add_argument('-l', '--show-log', dest='show_log', action='store_true',
                       help='Print git log of repositories.')
ARGPARSER.add_argument('-r', '--repo', dest='repo', action='store',
                       help='Specify a single repo rather than use depots.txt.')
ARGPARSER.add_argument('-m', '--moss-id', dest='mossid', action='store',
                       help='MOSS identifier. (See http://theory.stanford.edu/~aiken/moss/ to obtain an identifier.)')
ARGPARSER.add_argument('-o', '--show-output', dest='show_output', action='store_true',
                       help='Prints to screen the output of the programs evaluated.')
ARGS = ARGPARSER.parse_args()

# Verify timestamp format, if present.
if ARGS.timestamp:
    try:
        datetime.datetime.strptime(ARGS.timestamp, "%d/%m/%Y %H:%M")
    except ValueError:
        print('Bad timestamp', sys.exc_info())
        sys.exit(100)

subprocess.run('gcc -g -c ../main.c -o main.o', shell=True)

def evaluate_repo(name, timestamp=None):
    """Clone, compile and run tests on the given repo."""
    try:
        # Craft URL to clone given a depot name.
        remote_depot_name = name
        remote_depot_url = 'git@github.com:' + remote_depot_name + '.git'
        local_depot_path = remote_depot_name.replace('/', '-')
        print('=' * 10 + '\n' + local_depot_path)

        # Clone the repo.
        if (not os.path.exists(local_depot_path)):
            subprocess.run('git clone ' + remote_depot_url + ' ' + local_depot_path, shell=True, check=True, stderr=subprocess.PIPE)

        # If timestamp is specified, checkout at that point in time.
        timestamp = ARGS.timestamp or None
        if timestamp is not None:
            rev_list_cmd = subprocess.run('git rev-list -n 1 --before="' + timestamp + '" master', 
                                          cwd=local_depot_path, shell=True, capture_output=True, text=True, check=True)
            if not rev_list_cmd.stdout:
                raise RuntimeError('repo non-existant at timestamp: ' + timestamp)

            subprocess.run(['git checkout ' + rev_list_cmd.stdout], cwd=local_depot_path, shell=True, check=True, stderr=subprocess.PIPE)

        # Compile liste.c and link with main.o.
        subprocess.run('gcc --debug -I ../.. -c liste.c -o liste.o', cwd=local_depot_path, shell=True, check=True, stderr=subprocess.PIPE, text=True)
        subprocess.run('gcc --debug ../main.o liste.o -o a.out', cwd=local_depot_path, shell=True, check=True, stderr=subprocess.PIPE, text=True)

        # Launch tested program.
        run_program_cmd = subprocess.run('./a.out', cwd=local_depot_path, shell=True, capture_output=True, text=True, timeout=3)

        # Show results.
        if ARGS.show_output:
            print(run_program_cmd.stdout)
        else:
            print("\n".join(run_program_cmd.stdout.splitlines()[-3:]))

        # Show git log if requested.
        if ARGS.show_log:
            subprocess.run('git log --all --decorate --graph --pretty=format:"%aD (%an) %s"', cwd=local_depot_path, shell=True)

    except subprocess.CalledProcessError as e:
        print('Command "' + e.cmd + '" failed with error: [' + str(e.returncode) + '] ' + e.stderr)
    except subprocess.TimeoutExpired as e:
        print('Command "' + e.cmd + '" timed out with error: ' + e.stderr)
    except RuntimeError as e:
        print("Failure: " + "\n".join(e.args))

if __name__ == "__main__":
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
                            datetime.datetime.strptime(cells[1], "%d/%m/%Y %H:%M")
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
