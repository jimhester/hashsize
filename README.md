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

|     |  bucket\_length| front\_name                 |  front| back\_name                       |   back| med\_name                       |    med| total   | median  |
|-----|---------------:|:----------------------------|------:|:---------------------------------|------:|:--------------------------------|------:|:--------|:--------|
| 2   |              10| tidy.ftable                 |  0.028| qnt                              |  0.043| refMethodDef\#function          |  0.055| 53.57%  | 96.43%  |
| 210 |              10| UserHook::jsonlite::onLoad  |  0.051| validUTF8                        |  0.048| appendLF                        |  0.030| -5.88%  | -41.18% |
| 3   |              12| signifNum                   |  0.027| gl                               |  0.057| paged\_table\_type\_sum         |  0.050| 111.11% | 85.19%  |
| 4   |              10| lift\_ld                    |  0.018| .DollarNames.default             |  0.058| %||%                            |  0.029| 222.22% | 61.11%  |
| 5   |              10| lift\_ld                    |  0.018| .DollarNames.default             |  0.059| %||%                            |  0.026| 227.78% | 44.44%  |
| 6   |              10| intervals                   |  0.024| system                           |  0.044| print.check\_packages\_in\_dir  |  0.059| 83.33%  | 145.83% |
| 7   |              10| xml\_ns.xml\_document       |  0.041| blues9                           |  0.044| useHash                         |  0.032| 7.32%   | -21.95% |
| 8   |              12| signifNum                   |  0.026| gl                               |  0.050| paged\_table\_type\_sum         |  0.064| 92.31%  | 146.15% |
| 9   |              10| intervals                   |  0.023| system                           |  0.044| print.check\_packages\_in\_dir  |  0.059| 91.30%  | 156.52% |
| 10  |              10| Period                      |  0.016| as.Date.default                  |  0.055| select\_.data.frame             |  0.046| 243.75% | 187.50% |
| 11  |              11| dmicroseconds               |  0.030| setRepositories                  |  0.058| Variogram                       |  0.033| 93.33%  | 10.00%  |
| 12  |              10| xml\_find\_all              |  0.026| tolower                          |  0.053| CRAN\_baseurl\_for\_src\_area   |  0.063| 103.85% | 142.31% |
| 13  |              11| shift                       |  0.016| getAllConnections                |  0.064| True                            |  0.025| 300.00% | 56.25%  |
| 14  |              10| xml\_ns.xml\_document       |  0.039| blues9                           |  0.044| useHash                         |  0.029| 12.82%  | -25.64% |
| 15  |              11| as.hms.numeric              |  0.029| textConnectionValue              |  0.068| .\_\_T\_\_sqlParseVariables:DBI |  0.060| 134.48% | 106.90% |
| 16  |              10| as.ra\_ref\_v               |  0.031| isIncomplete                     |  0.054| vexpr                           |  0.027| 74.19%  | -12.90% |
| 17  |              10| R\_validate                 |  0.023| .Class                           |  0.045| generator\_funs                 |  0.038| 95.65%  | 65.22%  |
| 18  |              10| readxl\_xlsx\_date\_formats |  0.046| getVarsFromFrame                 |  0.058| knit\_code                      |  0.034| 26.09%  | -26.09% |
| 19  |              10| as\_list.xml\_nodeset       |  0.040| as.data.frame.numeric\_version   |  0.078| hook\_purl                      |  0.031| 95.00%  | -22.50% |
| 20  |              12| signifNum                   |  0.025| gl                               |  0.062| paged\_table\_type\_sum         |  0.051| 148.00% | 104.00% |
| 21  |              11| dmicroseconds               |  0.030| setRepositories                  |  0.056| Variogram                       |  0.035| 86.67%  | 16.67%  |
| 22  |              10| parse\_time                 |  0.022| ..33                             |  0.041| Module\_\_functions\_names      |  0.050| 86.36%  | 127.27% |
| 23  |              10| xml\_find\_all              |  0.026| tolower                          |  0.047| CRAN\_baseurl\_for\_src\_area   |  0.055| 80.77%  | 111.54% |
| 24  |              10| intervals                   |  0.023| system                           |  0.044| print.check\_packages\_in\_dir  |  0.060| 91.30%  | 160.87% |
| 25  |              10| tidy.density                |  0.026| &lt;.R\_system\_version          |  0.065| as.raster.array                 |  0.042| 150.00% | 61.54%  |
| 26  |              11| as.hms.numeric              |  0.031| textConnectionValue              |  0.067| .\_\_T\_\_sqlParseVariables:DBI |  0.059| 116.13% | 90.32%  |
| 27  |              12| read\_xml.session           |  0.035| alist                            |  0.053| keys.lookup                     |  0.034| 51.43%  | -2.86%  |
| 28  |              10| GeomLine                    |  0.023| xtfrm.POSIXlt                    |  0.053| DUMMY                           |  0.029| 130.43% | 26.09%  |
| 29  |              10| seq\_mnsl                   |  0.020| anyDuplicated.matrix             |  0.064| impMethods                      |  0.032| 220.00% | 60.00%  |
| 30  |              10| as\_list.xml\_nodeset       |  0.040| as.data.frame.numeric\_version   |  0.078| hook\_purl                      |  0.031| 95.00%  | -22.50% |
| 31  |              11| dmicroseconds               |  0.032| setRepositories                  |  0.058| Variogram                       |  0.035| 81.25%  | 9.38%   |
| 32  |              10| lift\_ld                    |  0.018| .DollarNames.default             |  0.058| %||%                            |  0.027| 222.22% | 50.00%  |
| 33  |              10| epi.bfi                     |  0.017| getDLLRegisteredRoutines.DLLInfo |  0.087| f1                              |  0.024| 411.76% | 41.18%  |
| 34  |              10| fullseq.POSIXt              |  0.032| .getNamespaceInfo                |  0.061| print.list.pairs                |  0.041| 90.62%  | 28.13%  |
| 35  |              10| fullseq.POSIXt              |  0.030| .getNamespaceInfo                |  0.058| print.list.pairs                |  0.041| 93.33%  | 36.67%  |
| 36  |              12| signifNum                   |  0.026| gl                               |  0.051| paged\_table\_type\_sum         |  0.049| 96.15%  | 88.46%  |
| 37  |              10| as\_list.xml\_nodeset       |  0.039| as.data.frame.numeric\_version   |  0.079| hook\_purl                      |  0.032| 102.56% | -17.95% |
| 38  |              10| seq\_mnsl                   |  0.019| anyDuplicated.matrix             |  0.061| impMethods                      |  0.031| 221.05% | 63.16%  |
| 39  |              10| is.namedlistnotdf           |  0.040| machine                          |  0.046| table2matrix                    |  0.036| 15.00%  | -10.00% |
| 40  |              10| glance.tbl\_df              |  0.030| &gt;.table                       |  0.045| knit\_root\_dir                 |  0.036| 50.00%  | 20.00%  |
| 41  |              10| GeomLine                    |  0.020| xtfrm.POSIXlt                    |  0.053| DUMMY                           |  0.026| 165.00% | 30.00%  |
| 42  |              12| signifNum                   |  0.024| gl                               |  0.050| paged\_table\_type\_sum         |  0.053| 108.33% | 120.83% |
| 43  |              10| R\_validate                 |  0.023| .Class                           |  0.043| generator\_funs                 |  0.039| 86.96%  | 69.57%  |
| 44  |              13| body\_raw                   |  0.023| rl\_word\_breaks                 |  0.075| rst\_muffle                     |  0.036| 226.09% | 56.52%  |
| 45  |              10| UserHook::jsonlite::onLoad  |  0.048| validUTF8                        |  0.048| appendLF                        |  0.030| -0.00%  | -37.50% |
| 46  |              11| dmicroseconds               |  0.030| setRepositories                  |  0.060| Variogram                       |  0.034| 100.00% | 13.33%  |
| 47  |              11| shift                       |  0.016| getAllConnections                |  0.066| True                            |  0.027| 312.50% | 68.75%  |
| 48  |              10| Period                      |  0.017| as.Date.default                  |  0.055| select\_.data.frame             |  0.047| 223.53% | 176.47% |
| 49  |              13| &lt;.POSIXt                 |  0.024| .isSingleString                  |  0.073| names.sql\_variant              |  0.044| 204.17% | 83.33%  |
| 50  |              10| log2\_trans                 |  0.022| Title                            |  0.044| simpleFormals                   |  0.038| 100.00% | 72.73%  |

Performance between current `HSIZE` and larger `HSIZE`.
-------------------------------------------------------

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

Hashed environment performance
------------------------------

An ideal hash would have constant time lookup regardless of hash size (third column).

HSIZE = 4119

    for i in {1..7};do Rscript inst/script2.R $((1 * 10**$i));done
    # 10      0.002   2e-04
    # 100     0.002   2e-05
    # 1000    0.002   2e-06
    # 10000   0.017   1.7e-06
    # 1e+05   0.263   2.63e-06
    # 1e+06   11.779  1.1779e-05
    # 1e+07 canceled after running for over an hour

HSIZE = 2^16

``` shell
for i in {1..7};do Rscript inst/script2.R $((1 * 10**$i));done
# 10      0.001   1e-04
# 100     0.001   1e-05
# 1000    0.00299999999999997     2.99999999999998e-06
# 10000   0.018   1.8e-06
# 1e+05   0.202   2.02e-06
# 1e+06   3.007   3.007e-06
# 1e+07   128.71  1.2871e-05
```
