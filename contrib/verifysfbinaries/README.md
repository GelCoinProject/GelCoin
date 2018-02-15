<<<<<<< HEAD
### Verify Binaries ###
=======
### Verify SF Binaries ###
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
This script attempts to download the signature file `SHA256SUMS.asc` from https://bitcoin.org.

It first checks if the signature passes, and then downloads the files specified in the file, and checks if the hashes of these files match those that are specified in the signature file.

<<<<<<< HEAD
The script returns 0 if everything passes the checks. It returns 1 if either the signature check or the hash check doesn't pass. If an error occurs the return value is 2.
=======
The script returns 0 if everything passes the checks. It returns 1 if either the signature check or the hash check doesn't pass. If an error occurs the return value is 2.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
