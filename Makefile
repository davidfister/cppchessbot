.PHONY: build run build-and-run flamegraph

BOT_VENV = $(CURDIR)/lichess-bot/venv


build:
	g++ $(CURDIR)/src/*.cpp -O4 -g -fno-omit-frame-pointer -o $(CURDIR)/src/engine.out
run: 
	cd lichess-bot && $(BOT_VENV)/bin/python3 lichess-bot.py

build-and-run: build run

flamegraph: 
	@TIME=$$(date '+%m_%d_%Hh%Mm'); \
	sudo sysctl kernel.perf_event_paranoid=1; \
	sudo perf record -g -o $(CURDIR)/FlameGraph/record/perf.data -- $(CURDIR)/src/engine.out benchmark; \
	sudo perf script -i $(CURDIR)/FlameGraph/record/perf.data | $(CURDIR)/FlameGraph/stackcollapse-perf.pl > $(CURDIR)/FlameGraph/record/out.perf-folded; \
	sudo $(CURDIR)/FlameGraph/flamegraph.pl $(CURDIR)/FlameGraph/record/out.perf-folded > $(CURDIR)/FlameGraph/lichess_benchmarks/lichess_$$TIME.svg; \
	sudo sysctl kernel.perf_event_paranoid=4; \

