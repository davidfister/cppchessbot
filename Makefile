.PHONY: build run build-and-run flamegraph build-debug

BOT_VENV = $(CURDIR)/lichess-bot/venv

build-debug:
	g++ $(CURDIR)/src/*.cpp -O2 -g -fno-omit-frame-pointer -fno-inline -flto -o $(CURDIR)/src/engine.out
build:
	g++ $(CURDIR)/src/*.cpp -Ofast -flto -o $(CURDIR)/src/engine.out
run: 
	cd lichess-bot && $(BOT_VENV)/bin/python3 lichess-bot.py

build-and-run: build run

flamegraph: build-debug
	@TIME=$$(date '+%m_%d_%Hh%Mm'); \
	sudo sysctl kernel.perf_event_paranoid=1; \
	sudo perf stat -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations,L1-dcache-loads:u,L1-dcache-load-misses -- $(CURDIR)/src/engine.out benchmark; \
	sudo perf record -g -o $(CURDIR)/FlameGraph/record/perf.data -- $(CURDIR)/src/engine.out benchmark; \
	sudo perf report -i $(CURDIR)/FlameGraph/record/perf.data; \
	sudo perf script -i $(CURDIR)/FlameGraph/record/perf.data | $(CURDIR)/FlameGraph/stackcollapse-perf.pl > $(CURDIR)/FlameGraph/record/out.perf-folded; \
	sudo $(CURDIR)/FlameGraph/flamegraph.pl $(CURDIR)/FlameGraph/record/out.perf-folded > $(CURDIR)/FlameGraph/lichess_benchmarks/lichess_$$TIME.svg; \
	sudo sysctl kernel.perf_event_paranoid=4; \

