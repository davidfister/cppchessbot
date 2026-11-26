import chess
import random
import csv


board = chess.Board()
print(board.legal_moves.count())
print(random.choice(list(board.legal_moves)))

with open('fens.csv', 'w', newline='') as csvfile:
    spamwriter = csv.writer(csvfile, delimiter=';')
    
    for n in range(1000):
        board = chess.Board()
        for i in range(100):
            spamwriter.writerow([board.fen()] + [board.legal_moves.count()])
            
            if board.legal_moves.count() != 0:
                board.push(random.choice(list(board.legal_moves)))

            if board.legal_moves.count() == 0:
                break
    
