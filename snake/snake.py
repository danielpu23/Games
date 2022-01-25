import curses
from random import randint

# window setup
curses.initscr()
win = curses.newwin(60, 20, 0, 0) # 60x20 board
win.keypad(1)
curses.noecho()
curses.curs_set(0)
win.border(0)
win.nodelay(1)

snake = [(5, 4), (5, 3), (5, 2)] # snake coordinates originally (size 3)
apple = (7, 7)

win.addch(apple[0], apple[1], '#')  # add apple to window

score = 0 # keeps track of score every time snake touches apple

ESC = 27
key = curses.KEY_RIGHT

while key != ESC:
    win.addstr(0, 2, 'Score ' + str(score) + ' ')

    prev_key = key
    event = win.getch()
    if event != -1:
        key = event
    else:
        key = prev_key

    # ignore keys that are not movement or esc
    if key not in [curses.KEY_LEFT, curses.KEY_RIGHT, curses.KEY_UP, curses.KEY_DOWN, ESC]:
        key = prev_key

    # calculate next coordinates
    y = snake[0][0]
    x = snake[0][1]
    if key == curses.KEY_DOWN:
        y += 1
    elif key == curses.KEY_UP:
        y -= 1
    elif key == curses.KEY_LEFT:
        x -= 1
    elif key == curses.KEY_RIGHT:
        x += 1

    snake.insert(0, (y, x)) # append snake's size after eating apple

    # snake dies if it hits the edge of screen
    if y == 0 or y == 19 or x == 0 or x == 59: break

    # if snake's head touches any part of its body then it dies as well
    if snake[0] in snake[1:]: break

    # if snake touches apple then it eats it and gains size
    if snake[0] == apple:

        score += 1
        apple = ()
        while apple == ():
            apple = (randint(1, 57), randint(1, 57)) # pick random spot to generate apple
            if apple in snake:  # also make sure it doesn't spawn in snake
                apple = ()
        win.addch(apple[0], apple[1], '#')
    else:
        last = snake.pop()
        win.addch(last[0], last[1], ' ')

    win.addch(snake[0][0], snake[0][1], '*')

curses.endwin()
print(f'Score = {score}')