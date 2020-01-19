n = int(input())
k = int(input())
# direct는 보드에서 뱀이 지나갈 때 생기는 방향을 표시
direct = []
# board는 맵
board = []

# direct가 -1이면 뱀이 없는 자리임
direct = [-1 for i in range(n) for j in range(n)]
board = [0 for i in range(n) for j in range(n)]

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

# 사과가 있는 자리는 보드를 2로 표시
for i in range(k):
    y, x = map(int, input().split())
    board[y - 1][x - 1] = 2

l = int(input())
# 10000밖에 안되므로 directionInfo를 길이 10001로 선언함.
# 시간을 directionInfo 리스트 인덱스로 활용
directionInfo = [0]*10001
for i in range(l):
    time, direction = list(map(str, input().split()))
    time = int(time)
    if direction == 'L':
        direction = -1
    else:
        direction = 1
    directionInfo[time] = direction

# 시간
timeCounter = 0
# 현재 방향 오른쪽
currentDirection = 0
# 꼬리좌표, 머리좌표
tail_y, tail_x = 0, 0
head_y, head_x = 0, 0

# 처음 시작하는 머리좌표 방향은 오른쪽
direct[head_y][head_x] = 0

while True:
    timeCounter += 1
    head_y += dy[currentDirection]
    head_x += dx[currentDirection]
    # 보드 벗어나면 탈출
    if head_y < 0 or head_y >= n or head_x < 0 or head_x >= n:
        break
    # 뱀이 자기 몸이랑 부딪치면 탈출
    elif board[head_y][head_x] == 1:
        break
    # 머리 내밀었는데 아무것도 없는 자리이면
    if board[head_y][head_x] == 0:
        # 꼬리 없앰
        board[tail_y][tail_x] = 0
        # 꼬리가 어디로 나아가야할 지 direct에 저장해놓은 값을 tailDirection에 저장
        tailDirection = direct[tail_y][tail_x]
        # 꼬리에 있던 direct 없앰(꼬리가 없어졌으니)
        direct[tail_y][tail_x] = -1
        # 꼬리 진행
        tail_y += dy[tailDirection]
        tail_x += dx[tailDirection]

    # 공통적으로 뱀 머리가 나아가면 board를 1로 표시
    board[head_y][head_x] = 1

    # 해당 시간에 direction 변화가 있는지 체크
    if directionInfo[timeCounter] == 0:
        pass
    else:
        # 왼쪽으로 틀음
        if directionInfo[timeCounter] == -1:
            currentDirection = (currentDirection + 3) % 4

        # 오른쪽으로 틀음
        else:
            currentDirection = (currentDirection + 1) % 4
    # 모든 작업이 끝나고 머리 방향을 틀음
    direct[head_y][head_x] = currentDirection
print(timeCounter)
