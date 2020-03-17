from subprocess import Popen, PIPE, STDOUT, TimeoutExpired

def run(command, process_input):
    process = Popen(command, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT)

    try:
        out = process.communicate(input=process_input, timeout=10)[0]
    except TimeoutExpired:
        process.kill()
        return (1, "")

    code = process.wait()
    return code, out

def test(command, process_input, expected_code):
    code, out = run(command, process_input)

    if (code != expected_code):
        print('Invalid return value')
        return

    l = list()
    try:
        l = out.decode('ascii').split('\n')
    except:
        print('Invalid output')
        return

    if ((l[0] != 'Begin') | (l[1] != 'S: Starting1') | (l[3] != 'End') | (l[7] != 'S: 1st') |  (l[14] != 'N: 3') | (l[17] != 'End')):
        print('WA')
        return

    print('Success')

test('./parcer',  b'''4 Starting1 test
                    This is 1st string
                    Numbers 1 2 03
                        ''', 0)
