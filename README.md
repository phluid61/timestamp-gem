timestamp
=========

```ruby
# Nanosecond monotonic clock:
Time.timestamp       #=> int
# Seconds since the Epoch:
Time.unix_timestamp  #=> int
Time.unix_microtime  #=> float
```

Benchmarks
----------

Tested on two similarly-spec'd Ubuntu VMs, using a recent ruby 2.1.0 build.

### 64-Bit VM:
```
                           user     system      total        real
Time.now.to_i          0.080000   5.440000   5.520000 (  5.533965)
Time.unix_timestamp    0.060000   0.000000   0.060000 (  0.060482)

Time.now.to_f          0.180000   6.840000   7.020000 (  7.012264)
Time.unix_microtime    0.020000   4.190000   4.210000 (  4.209150)

Time.timestamp         0.040000   4.340000   4.380000 (  4.384826)
```
### 32-Bit VM:
```
Time.now.to_i          0.200000   5.310000   5.510000 (  5.523720)
Time.unix_timestamp    0.160000   0.030000   0.190000 (  0.183468)

Time.now.to_f          0.340000   5.260000   5.600000 (  5.602743)
Time.unix_microtime    0.140000   4.160000   4.300000 (  4.301589)

Time.timestamp         0.070000   4.320000   4.390000 (  4.392840)
```

* [Contributor Code of Conduct](code_of_conduct.md)
* [![Build Status](https://travis-ci.org/phluid61/timestamp-gem.png)](https://travis-ci.org/phluid61/timestamp-gem)

