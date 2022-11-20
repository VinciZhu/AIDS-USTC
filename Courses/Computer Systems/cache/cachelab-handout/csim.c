#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Globals set on the command line */
static int s = 0; // Number of set index bits
static int E = 0; // Number of lines per set
static int b = 0; // Number of block offset bits
static int verbose_mode = 0;
static char *trace_file = NULL;

/* Struct for cache lines */
typedef struct cache_line {
  int count; // Number of times this line has been accessed
  int valid;
  unsigned int tag;
} cache_line_t, *cache_set_t, **cache_t;
static cache_t cache;

/* Globals for cache statistics */
static int num_hits = 0;
static int num_misses = 0;
static int num_evictions = 0;

/*
 * usage - Print usage info
 */
void usage(char *argv[]) {
  printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>", argv[0]);
  printf("Options:\n");
  printf("  -h         Print this help message.\n");
  printf("  -v         Optional verbose flag.");
  printf("  -s <num>   Number of set index bits.\n");
  printf("  -E <num>   Number of lines per set.\n");
  printf("  -b <num>   Number of block offset bits.\n");
  printf("  -t <file>  Trace file.\n");
  printf("\n");
  printf("Examples:\n");
  printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
  printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
}

/*
 * parseArgs - Parse the command line arguments
 */
void parseArgs(int argc, char *argv[]) {
  char c;

  while ((c = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
    switch (c) {
    case 's':
      s = atoi(optarg);
      break;
    case 'E':
      E = atoi(optarg);
      break;
    case 'b':
      b = atoi(optarg);
      break;
    case 't':
      trace_file = optarg;
      break;
    case 'v':
      verbose_mode = 1;
      break;
    case 'h':
      usage(argv);
      exit(0);
    default:
      usage(argv);
      exit(1);
    }
  }
}

/*
 * initCache - Initialize the cache with s, E and b
 */
void initCache() {
  int S = 1 << s; // Number of sets
  cache = malloc(sizeof(cache_set_t) * S);
  for (int i = 0; i < S; i++)
    cache[i] = calloc(E, sizeof(cache_line_t));
}

/*
 * deinitCache - Deinitialize the cache
 */
void deinitCache() {
  int S = 1 << s; // Number of sets
  for (int i = 0; i < S; i++)
    free(cache[i]);
  free(cache);
}

/*
 * accessCache - Simulate to access cache
 */
void accessCache(char op, unsigned int addr, int size) {

  /* Calculate tag in address */
  unsigned int tag = addr >> (s + b);
  /* Get cache set by index */
  cache_set_t set = cache[addr >> b & ((1 << s) - 1)];

  /* 'M' operation always results in an extra hit */
  if (op == 'M')
    num_hits++;

  if (verbose_mode)
    printf("%c %x,%d ", op, addr, size);

  /* Check if there is a hit */
  int empty = -1, lru = 0;
  for (int i = 0; i < E; i++) {
    if (!set[i].valid)
      empty = i; // Search for an empty line
    else if (set[i].tag == tag) {
      if (verbose_mode)
        printf(op == 'M' ? "hit hit\n" : "hit\n");
      num_hits++;
      set[i].count = 0; // Update time count using LRU policy
      return;
    } else if (++set[i].count >= set[lru].count)
      lru = i; // Search for the LRU line
  }

  /* If there is no empty line, evict the LRU line */
  cache_line_t *line;
  if (empty >= 0) {
    if (verbose_mode)
      printf(op == 'M' ? "miss hit\n" : "miss\n");
    line = &set[empty];
  } else {
    if (verbose_mode)
      printf(op == 'M' ? "miss eviction hit\n" : "miss eviction\n");
    line = &set[lru];
    num_evictions++;
  }
  line->valid = 1;
  line->tag = tag;
  line->count = 0;
  num_misses++;
}

/*
 * main - Main routine
 */
int main(int argc, char *argv[]) {
  parseArgs(argc, argv);
  initCache();
  FILE *trace_fp = fopen(trace_file, "r");

  char line[32];
  while (fgets(line, 32, trace_fp)) {
    /* Ignore instruction cache accesses */
    if (line[0] == 'I')
      continue;

    /* Parse operation */
    char op;
    unsigned int addr;
    int size;
    sscanf(line, " %c %x,%d", &op, &addr, &size);

    accessCache(op, addr, size);
  }

  fclose(trace_fp);
  deinitCache();
  printSummary(num_hits, num_misses, num_evictions);
  return 0;
}