import collections
import itertools
from typing import List


def solve_parameterized(
    k_target_attacks, board_width, board_height, obstacle_coordinates_set
) -> List[List[int]]:
    empty_cells_for_placing_queens = []
    for r_idx in range(board_height):
        for c_idx in range(board_width):
            if (r_idx, c_idx) not in obstacle_coordinates_set:
                empty_cells_for_placing_queens.append((r_idx, c_idx))

    target_cells_to_cover = set(empty_cells_for_placing_queens)

    min_queens_found = float("inf")
    solutions_coords = []

    for num_queens_to_place in range(len(empty_cells_for_placing_queens) + 1):
        if num_queens_to_place > min_queens_found and min_queens_found != float("inf"):
            break

        for current_queen_positions_tuple in itertools.combinations(
            empty_cells_for_placing_queens, num_queens_to_place
        ):
            current_queen_positions = list(current_queen_positions_tuple)

            attack_coverage = collections.defaultdict(int)

            for queen_r, queen_c in current_queen_positions:
                attack_coverage[(queen_r, queen_c)] += 1

                directions = [
                    (-1, 0),
                    (1, 0),
                    (0, -1),
                    (0, 1),
                    (-1, -1),
                    (-1, 1),
                    (1, -1),
                    (1, 1),
                ]
                for dr, dc in directions:
                    curr_r, curr_c = queen_r + dr, queen_c + dc
                    while 0 <= curr_r < board_height and 0 <= curr_c < board_width:
                        if (curr_r, curr_c) in obstacle_coordinates_set:
                            break
                        attack_coverage[(curr_r, curr_c)] += 1
                        curr_r += dr
                        curr_c += dc

            is_valid_config = True
            if not target_cells_to_cover:
                pass
            else:
                for r_check, c_check in target_cells_to_cover:
                    if attack_coverage[(r_check, c_check)] < k_target_attacks:
                        is_valid_config = False
                        break

            if is_valid_config:
                sorted_queen_positions_list_of_tuples = sorted(current_queen_positions)

                if num_queens_to_place < min_queens_found:
                    min_queens_found = num_queens_to_place
                    solutions_coords = [sorted_queen_positions_list_of_tuples]
                elif num_queens_to_place == min_queens_found:
                    solutions_coords.append(sorted_queen_positions_list_of_tuples)

    final_output_list_of_lists_of_ints = []
    if solutions_coords:
        solutions_coords.sort()

        for sol_coords_list_of_tuples in solutions_coords:
            flat_sol_ints = []
            for r_coord, c_coord in sol_coords_list_of_tuples:
                flat_sol_ints.extend([r_coord, c_coord])
            final_output_list_of_lists_of_ints.append(flat_sol_ints)

    return final_output_list_of_lists_of_ints


def find_queens_placements_from_file(filename="input.txt") -> List[List[int]]:
    with open(filename, "r") as f_in:
        k = int(f_in.readline().strip())
        w, h = map(int, f_in.readline().strip().split())
        n_obstacles = int(f_in.readline().strip())

        obstacles_set = set()
        for _ in range(n_obstacles):
            r_str, c_str = f_in.readline().strip().split()
            obstacles_set.add((int(r_str), int(c_str)))

    return solve_parameterized(k, h, w, obstacles_set)


if __name__ == "__main__":
    # Эта функция find_queens_placements_from_file - это то, что требуется по условию:
    # "код на питоне, который просто берет из файла input.txt данные и полным перебором
    # находит ответ и возвращает как List[List[int]]"

    # Для запуска:
    # 1. Убедитесь, что файл "input.txt" с данными из примера находится в той же директории.
    # 2. Запустите этот скрипт.
    # 3. Результат (List[List[int]]) будет вычислен.
    #    Чтобы увидеть его в консоли, раскомментируйте следующие строки:

    solutions = find_queens_placements_from_file("input.txt")
    print(f"Number of solutions: {len(solutions)}")  # Это m из условия вывода
    for i, sol_flat_list in enumerate(solutions):
        # Преобразуем список чисел в строку, разделенную пробелами
        # Если sol_flat_list пуст (0 ферзей), join вернет пустую строку.
        print(f"Solution {i + 1}: {' '.join(map(str, sol_flat_list))}")

    # В рамках задачи, функция find_queens_placements_from_file просто возвращает результат,
    # а вывод в нужном формате должен осуществляться вызывающим кодом.
