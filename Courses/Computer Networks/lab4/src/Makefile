# Build
CS_TARGET := echo udp
INC := -I common

.PHONY: all
all: $(CS_TARGET) tcp

%: %.c
	gcc $(INC) $< -o $@

.PHONY: $(CS_TARGET)
$(CS_TARGET): %: %/client %/server | git-sync

.PHONY: tcp
tcp: tcp/tcp | git-sync

.PHONY .SILENT: clean
clean:
	rm -f $(CS_TARGET:%=%/client)
	rm -f $(CS_TARGET:%=%/server)
	rm -f tcp/tcp

# Start server
IP := $(shell ifconfig 2>/dev/null| grep -oe 'inet [0-9\.]\+' |\
 grep -v '127.0.0.1\|172.19.0.1' | cut -d\  -f2)
PORT := 8080

.PHONY: $(CS_TARGET:%=%-server)
$(CS_TARGET:%=%-server): %-server: %/server | git-sync
	$< $(IP) $(PORT)

# Sync source between local and remote
HOST_NAME := $(shell hostname)
.PHONY .SILENT: git-sync
git-sync:
	git pull --quiet
	git diff --quiet ||\
	git commit -am 'Sync from $(HOST_NAME)' &&\
	git push --quiet

