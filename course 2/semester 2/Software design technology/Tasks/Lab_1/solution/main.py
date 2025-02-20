def read_file_and_make_data(file):
    amount_relatives = int(file.readline())
    if amount_relatives < 15:
        print("\t***Количество родственников должно быть 15 и более!***")
        exit(1)
    tree = {}
    amount_generation = 0
    for _ in range(amount_relatives):
        line = file.readline().strip()
        if ':' in line:
            amount_generation += 1
            child, parents = line.split(':')
            tree[child.strip()] = [parent.strip() for parent in parents.split()]
        else:
            tree[line.strip()] = []
    if amount_generation < 4:
        print("\t***Количество поколений должно быть 4 и более!***")
        exit(1)
    amount_checks = int(file.readline())
    if amount_checks < 15:
        print("\t***Количество проверок должно быть 15 и более!***")
        exit(1)
    list_check = []
    for _ in range(amount_checks):
        line = file.readline().split()
        ancestor = line[0]
        result = line[-1]
        descendant = line[1:-1]
        list_check.append((ancestor, " ".join(descendant), result == 'Да'))
    return tree, list_check


def is_ancestor(tree, ancestor, descendant):
    if ancestor == descendant:
        return True
    return any(is_ancestor(tree, ancestor, parent) for parent in tree.get(descendant, []))


if __name__ == '__main__':
    while True:
        try:
            file = open(input("Введите путь к файлу -> ").strip('"'), 'r', encoding='utf-8')
            break
        except FileNotFoundError:
            print("\t***Не удалось найти файл!***")
    tree, list_check = read_file_and_make_data(file)
    file.close()
    for ancestor, descendant, result in list_check:
        assert is_ancestor(tree, ancestor, descendant) == result, f"Ошибка: Предок {ancestor}, потомок {descendant}, правильный ответ {"Нет" if result else "Да"}"