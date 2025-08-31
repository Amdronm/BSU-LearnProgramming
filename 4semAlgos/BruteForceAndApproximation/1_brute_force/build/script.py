"""
generate input.txt
start cpp solve
find brute force solve
read solve from output.txt
compare answers
"""

import os
from random import randint
import subprocess
from typing import List
from solver import find_queens_placements_from_file


def GenerateInput(width: int, height: int) -> None:
    obs = set()
    width = randint(1, width)
    height = randint(1, height)
    k = randint(1, width + height)
    obstacles = randint(1, width + height)
    for _ in range(obstacles):
        obs.add((randint(0, height - 1), randint(0, width - 1)))
    with open("input.txt", "w") as input:
        input.write(f"{k}\n{height} {width}\n{len(obs)}\n")
        for row, col in obs:
            input.write(f"{row} {col}\n")


def StartAlgo() -> None:
    proc = subprocess.Popen("./brute_force", stdout=subprocess.PIPE)
    if proc.stdout:
        lines = proc.stdout.readlines()
        for line in lines:
            print(line.decode().strip())

    ret_code = proc.wait()
    if ret_code == 0:
        Compare()
    else:
        Log("RTE", [])


def ProcOnlyAlgo():
    proc = subprocess.Popen("./brute_force", stdout=subprocess.PIPE)
    if proc.stdout:
        lines = proc.stdout.readlines()
        for line in lines:
            print(line.decode().rstrip())


def Compare() -> None:
    brute_solution = sorted(find_queens_placements_from_file())
    algo_solution = []
    with open("output.txt") as output:
        for line in output.readlines():
            algo_solution.append(list(map(int, line.split())))
    tup_sol = list(map(tuple, algo_solution.__iter__()))
    tup_sol.sort()
    algo_solution = []
    for row in tup_sol:
        algo_solution.append(list(row))
    if algo_solution == brute_solution or (
        not algo_solution and len(brute_solution) == 1 and brute_solution[0] == []
    ):
        print("yes")
    else:
        print("no")
        Log("WA", brute_solution)


def Log(mess: str, ans: List[List[int]]) -> None:
    to_log = ""
    to_log_out = ""
    with open("input.txt") as input:
        to_log = input.read()
    with open("output.txt") as output:
        to_log_out = output.read()
    with open("errors_log.txt", "a") as log:
        log.write(f"{mess}\n")
        log.write(f"INPUT\n{to_log}\n")
        log.write(f"OUTPUT\n{to_log_out}\n")


if __name__ == "__main__":
    file_path = "errors_log.txt"
    if os.path.exists(file_path):
        os.remove(file_path)
    for i in range(100):
        print(f"test {i + 1} ")
        GenerateInput(4, 5)
        StartAlgo()
        # ProcOnlyAlgo()
