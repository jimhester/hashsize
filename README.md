<!-- README.md is generated from README.Rmd. Please edit that file -->
``` r
library(hashsize)

# Load the tidyverse to populate the symbol table
suppressPackageStartupMessages(library(tidyverse))

buckets <- .Call(hashsize:::hashsize_symbols, 4119L)
lens <- lengths(buckets)
total <- sum(lens)
total
#> [1] 17666
summary(lens)
#>    Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
#>   0.000   3.000   4.000   4.289   6.000  13.000
hist(lens)
```

![](inst/README-example-1.png)

``` r

elapsed_time <- function(expr) system.time(expr)[[3]]

time_large_bucket <- function(buckets, n, median, times = 1e8) {
  b <- buckets[lengths(buckets) >= n]
  b <- b[[sample.int(length(b), 1)]]

  front <- as.character(b[[1]])
  back <- as.character(b[[length(b)]])
  med <- as.character(b[[median]])
  list(
    bucket_length = length(b),
    front_name = front,
    front = elapsed_time(.Call(hashsize:::hashsize_lookup_bench, front, times)),
    back_name = back,
    back = elapsed_time(.Call(hashsize:::hashsize_lookup_bench, back, times)),
    med_name = med,
    med = elapsed_time(.Call(hashsize:::hashsize_lookup_bench, med, times)))
}

to_df <- function(x) {
  df <- do.call(rbind.data.frame, x)

  percent <- function(x) sprintf("%.2f%%", x * 100)

  df$total <- percent((df$back - df$front) / df$front)
  df$median <- percent((df$med - df$front) / df$front)
  df
}

knitr::kable(
  to_df(replicate(50, time_large_bucket(buckets, 10, 5, 1e6), simplify = FALSE)))
```

|     |  bucket\_length| front\_name                |  front| back\_name                       |   back| med\_name                       |    med| total   | median  |
|-----|---------------:|:---------------------------|------:|:---------------------------------|------:|:--------------------------------|------:|:--------|:--------|
| 2   |              11| as.hms.numeric             |  0.032| textConnectionValue              |  0.065| .\_\_T\_\_sqlParseVariables:DBI |  0.064| 103.12% | 100.00% |
| 210 |              10| Date\#Duration             |  0.030| within.data.frame                |  0.062| repair\_names                   |  0.036| 106.67% | 20.00%  |
| 3   |              10| R\_validate                |  0.027| .Class                           |  0.048| generator\_funs                 |  0.039| 77.78%  | 44.44%  |
| 4   |              10| epi.bfi                    |  0.017| getDLLRegisteredRoutines.DLLInfo |  0.087| f1                              |  0.024| 411.76% | 41.18%  |
| 5   |              10| intervals                  |  0.020| system                           |  0.043| print.check\_packages\_in\_dir  |  0.058| 115.00% | 190.00% |
| 6   |              10| xml\_ns.xml\_document      |  0.035| blues9                           |  0.042| useHash                         |  0.028| 20.00%  | -20.00% |
| 7   |              10| circadian.phase            |  0.029| is.stepfun                       |  0.051| grid.rect                       |  0.031| 75.86%  | 6.90%   |
| 8   |              10| lift\_ld                   |  0.017| .DollarNames.default             |  0.056| %||%                            |  0.026| 229.41% | 52.94%  |
| 9   |              10| TokenServiceAccount        |  0.041| R\_system\_version               |  0.058| add1                            |  0.026| 41.46%  | -36.59% |
| 10  |              10| as\_list.xml\_nodeset      |  0.036| as.data.frame.numeric\_version   |  0.083| hook\_purl                      |  0.040| 130.56% | 11.11%  |
| 11  |              10| xml\_ns.xml\_document      |  0.042| blues9                           |  0.044| useHash                         |  0.029| 4.76%   | -30.95% |
| 12  |              10| xml\_ns.xml\_document      |  0.039| blues9                           |  0.042| useHash                         |  0.028| 7.69%   | -28.21% |
| 13  |              10| log2\_trans                |  0.025| Title                            |  0.044| simpleFormals                   |  0.038| 76.00%  | 52.00%  |
| 14  |              10| seq\_mnsl                  |  0.022| anyDuplicated.matrix             |  0.059| impMethods                      |  0.032| 168.18% | 45.45%  |
| 15  |              11| dmicroseconds              |  0.026| setRepositories                  |  0.054| Variogram                       |  0.031| 107.69% | 19.23%  |
| 16  |              10| Period                     |  0.018| as.Date.default                  |  0.057| select\_.data.frame             |  0.047| 216.67% | 161.11% |
| 17  |              10| GeomLine                   |  0.023| xtfrm.POSIXlt                    |  0.051| DUMMY                           |  0.026| 121.74% | 13.04%  |
| 18  |              10| lift\_ld                   |  0.018| .DollarNames.default             |  0.057| %||%                            |  0.025| 216.67% | 38.89%  |
| 19  |              10| Period                     |  0.017| as.Date.default                  |  0.058| select\_.data.frame             |  0.049| 241.18% | 188.24% |
| 20  |              10| tidy.ftable                |  0.024| qnt                              |  0.044| refMethodDef\#function          |  0.050| 83.33%  | 108.33% |
| 21  |              10| seq\_mnsl                  |  0.023| anyDuplicated.matrix             |  0.059| impMethods                      |  0.032| 156.52% | 39.13%  |
| 22  |              10| reclass\_date.POSIXlt      |  0.041| :::                              |  0.042| S3Part&lt;-                     |  0.029| 2.44%   | -29.27% |
| 23  |              10| TokenServiceAccount        |  0.044| R\_system\_version               |  0.058| add1                            |  0.026| 31.82%  | -40.91% |
| 24  |              11| write\_xml.xml\_nodeset    |  0.040| ..59                             |  0.045| stri\_extract                   |  0.037| 12.50%  | -7.50%  |
| 25  |              11| as.hms.numeric             |  0.032| textConnectionValue              |  0.064| .\_\_T\_\_sqlParseVariables:DBI |  0.064| 100.00% | 100.00% |
| 26  |              10| epi.bfi                    |  0.017| getDLLRegisteredRoutines.DLLInfo |  0.087| f1                              |  0.024| 411.76% | 41.18%  |
| 27  |              10| xml\_ns.xml\_document      |  0.035| blues9                           |  0.047| useHash                         |  0.033| 34.29%  | -5.71%  |
| 28  |              11| as.hms.numeric             |  0.031| textConnectionValue              |  0.064| .\_\_T\_\_sqlParseVariables:DBI |  0.064| 106.45% | 106.45% |
| 29  |              10| circular                   |  0.020| Sys.setFileTime                  |  0.064| tick\_non\_syntactic            |  0.048| 220.00% | 140.00% |
| 30  |              10| tidy.density               |  0.035| &lt;.R\_system\_version          |  0.062| as.raster.array                 |  0.047| 77.14%  | 34.29%  |
| 31  |              10| tidy.ftable                |  0.024| qnt                              |  0.044| refMethodDef\#function          |  0.053| 83.33%  | 120.83% |
| 32  |              10| R\_validate                |  0.025| .Class                           |  0.044| generator\_funs                 |  0.045| 76.00%  | 80.00%  |
| 33  |              10| modulo\_period\_by\_period |  0.045| as.data.frame.integer            |  0.058| on\_failure&lt;-                |  0.036| 28.89%  | -20.00% |
| 34  |              10| TokenServiceAccount        |  0.040| R\_system\_version               |  0.057| add1                            |  0.030| 42.50%  | -25.00% |
| 35  |              10| circadian.phase            |  0.029| is.stepfun                       |  0.049| grid.rect                       |  0.031| 68.97%  | 6.90%   |
| 36  |              10| intervals                  |  0.020| system                           |  0.042| print.check\_packages\_in\_dir  |  0.059| 110.00% | 195.00% |
| 37  |              10| parse\_time                |  0.023| ..33                             |  0.040| Module\_\_functions\_names      |  0.052| 73.91%  | 126.09% |
| 38  |              10| modulo\_period\_by\_period |  0.048| as.data.frame.integer            |  0.058| on\_failure&lt;-                |  0.036| 20.83%  | -25.00% |
| 39  |              10| reclass\_date.POSIXlt      |  0.045| :::                              |  0.043| S3Part&lt;-                     |  0.030| -4.44%  | -33.33% |
| 40  |              12| signifNum                  |  0.025| gl                               |  0.054| paged\_table\_type\_sum         |  0.049| 116.00% | 96.00%  |
| 41  |              10| is.namedlistnotdf          |  0.033| machine                          |  0.044| table2matrix                    |  0.037| 33.33%  | 12.12%  |
| 42  |              10| xml\_find\_all             |  0.027| tolower                          |  0.052| CRAN\_baseurl\_for\_src\_area   |  0.055| 92.59%  | 103.70% |
| 43  |              10| xml\_ns.xml\_document      |  0.036| blues9                           |  0.043| useHash                         |  0.032| 19.44%  | -11.11% |
| 44  |              10| lift\_ld                   |  0.021| .DollarNames.default             |  0.058| %||%                            |  0.026| 176.19% | 23.81%  |
| 45  |              10| circadian.phase            |  0.028| is.stepfun                       |  0.050| grid.rect                       |  0.033| 78.57%  | 17.86%  |
| 46  |              12| signifNum                  |  0.022| gl                               |  0.056| paged\_table\_type\_sum         |  0.053| 154.55% | 140.91% |
| 47  |              11| as.hms.numeric             |  0.033| textConnectionValue              |  0.068| .\_\_T\_\_sqlParseVariables:DBI |  0.070| 106.06% | 112.12% |
| 48  |              10| GeomLine                   |  0.026| xtfrm.POSIXlt                    |  0.063| DUMMY                           |  0.031| 142.31% | 19.23%  |
| 49  |              11| dmicroseconds              |  0.028| setRepositories                  |  0.063| Variogram                       |  0.033| 125.00% | 17.86%  |
| 50  |              11| .duration\_from\_num       |  0.040| .Group                           |  0.050| stri\_read\_raw                 |  0.040| 25.00%  | 0.00%   |

Performance between current `HSIZE` and larger `HSIZE`.
=======================================================

<inst/script.R> has a simple benchmark, to compare between the current value and a larger one. The benchmark looks up every symbol in the hash a certain number of times (10,000 in this example).

``` shell
R --version
# R Under development (unstable) (2017-05-16 r72682) -- "Unsuffered Consequences"

# Current HSIZE (4119)
Rscript inst/script.R 4119 $((10**4))
# [1] 15959
#    user  system elapsed
#   5.245   0.005   5.252

# HSIZE of 2^16 (65536)
Rscript inst/script.R $((2**16)) $((10**4))
# [1] 16093
#    user  system elapsed
#   4.280   0.007   4.288
```
