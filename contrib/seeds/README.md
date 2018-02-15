<<<<<<< HEAD
### Seeds ###
=======
# Seeds
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Utility to generate the seeds.txt list that is compiled into the client
(see [src/chainparamsseeds.h](/src/chainparamsseeds.h) and other utilities in [contrib/seeds](/contrib/seeds)).

<<<<<<< HEAD
The seeds compiled into the release are created from sipa's DNS seed data, like this:

    curl -s http://bitcoin.sipa.be/seeds.txt > seeds_main.txt
    python makeseeds.py < seeds_main.txt > nodes_main.txt
    python generate-seeds.py . > ../../src/chainparamsseeds.h

=======
Be sure to update `PATTERN_AGENT` in `makeseeds.py` to include the current version,
and remove old versions as necessary.

The seeds compiled into the release are created from fuzzbawls' DNS seed data, like this:

    curl -s http://seeder.fuzzbawls.pw/lux-mainnet.txt > seeds_main.txt
    python3 makeseeds.py < seeds_main.txt > nodes_main.txt
    python3 generate-seeds.py . > ../../src/chainparamsseeds.h

## Dependencies

Ubuntu:

    sudo apt-get install python3-dnspython
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
