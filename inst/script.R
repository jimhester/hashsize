library(hashsize)
suppressPackageStartupMessages(library(tidyverse))

num <- tail(commandArgs(), n = 2)[[1]]
times <- tail(commandArgs(), n = 2)[[2]]
s <- as.character(unlist(.Call(hashsize_symbols, as.integer(num))))

print(length(s))

#microbenchmark::microbenchmark({
system.time({
  for (symbol in s) {
    .Call(hashsize:::hashsize_lookup_bench, symbol, as.numeric(times))
  }
})
