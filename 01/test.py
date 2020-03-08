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

    if ((int(l[2] , 16) != int(l[1], 16)) | (int(l[3], 16) - int(l[2], 16) != 50) | (int(l[4], 16) != 0) |
        (int(l[7], 16) - int(l[6], 16) != 100) | (int(l[8], 16) != 0) | (int(l[11], 16) != 0) | 
        (int(l[14], 16) != 0)):
        print('WA')
        return

    print('Success')

test('./a.out',  b'''makeAllocator 100
                    alloc 0
                    alloc 50
                    alloc 50
                    alloc 1
                    reset
                    alloc 100
                    alloc 0
                    alloc 1
                    reset
                    alloc 24
                    alloc -1
                    exit
                    makeAllocator -1
                    alloc 0
                    break''', 0)
