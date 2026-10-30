.PHONY: build run build-and-run

BOT_VENV = $(CURDIR)/lichess-bot/venv


build:
	g++ $(CURDIR)/src/*.cpp -O4 -g -o $(CURDIR)/src/engine.out
run: 
	cd lichess-bot && $(BOT_VENV)/bin/python3 lichess-bot.py

build-and-run: build run