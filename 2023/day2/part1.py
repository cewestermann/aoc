

with open('input.txt', 'r') as f:
    data = f.readlines()

impossible = False

pos_sum = 0
possible_ids = []
for line in data:
    ids, imppart = line.split(':')
    gameid = int(ids.split(' ')[-1])
    draws = imppart.split(';')
    possible = True
    for draw in draws:
        individual_draw = draw.split(',')
        for subdraw in individual_draw:
            number, type_ = subdraw.strip().split(' ')

            if type_ == 'red' and int(number) > 12: possible = False
            if type_ == 'green' and int(number) > 13: possible = False
            if type_ == 'blue' and int(number) > 14: possible = False

    if possible:
        print(gameid)
        possible_ids.append(gameid)

print(sum(possible_ids))

