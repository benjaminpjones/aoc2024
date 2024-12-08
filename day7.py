def parseLine(s):
    parts = s.split(":")
    number_before_colon = int(parts[0].strip())  # Convert the part before the colon to an integer
    numbers_after_colon = list(map(int, parts[1].strip().split()))  # Split and convert the part after the colon to integers
    return number_before_colon, numbers_after_colon

def isValid(lhs, rhs, currVal, currIdx):
    if currIdx == len(rhs):
        return lhs == currVal

    return (isValid(lhs, rhs, currVal * rhs[currIdx], currIdx+1)
            or isValid(lhs, rhs, currVal + rhs[currIdx], currIdx + 1)
            or isValid(lhs, rhs, int(str(currVal) + str(rhs[currIdx])), currIdx + 1))

tot = 0
while line := input():
    lhs, rhs = parseLine(line)
    if isValid(lhs, rhs, rhs[0], 1):
        tot += lhs
print("tot", tot)
