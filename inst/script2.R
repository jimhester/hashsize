library(hashsize)

env <- new.env(hash = TRUE, parent = emptyenv())

# generate random keys and add them to a hash

num <- as.numeric(tail(commandArgs(), n = 1))

for (i in seq_len(num)) {
  key <- paste(collapse = "", sample(letters)[seq_len(sample(length(letters), size = 1))])
  env[[key]] <- 1
}

# Lookup all keys in the hash
keys <- names(env)
time <- system.time({
  for (k in keys) {
    exists(k, where = env)
  }
})

cat(paste0(num, "\t", time[3], "\t", as.numeric(time[3]) / num), "\n")
