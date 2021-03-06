<<<<<<< HEAD
Sample init scripts and service configuration for gelcoind
=======
Sample init scripts and service configuration for luxd
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

<<<<<<< HEAD
    contrib/init/gelcoind.service:    systemd service unit configuration
    contrib/init/gelcoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/gelcoind.openrcconf: OpenRC conf.d file
    contrib/init/gelcoind.conf:       Upstart service configuration file
    contrib/init/gelcoind.init:       CentOS compatible SysV style init script
=======
    contrib/init/luxd.service:    systemd service unit configuration
    contrib/init/luxd.openrc:     OpenRC compatible SysV style init script
    contrib/init/luxd.openrcconf: OpenRC conf.d file
    contrib/init/luxd.conf:       Upstart service configuration file
    contrib/init/luxd.init:       CentOS compatible SysV style init script
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

1. Service User
---------------------------------

<<<<<<< HEAD
All three Linux startup configurations assume the existence of a "gelcoincore" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes gelcoind will be set up for the current user.
=======
All three startup configurations assume the existence of a "lux" user
and group.  They must be created before attempting to use these scripts.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

2. Configuration
---------------------------------

<<<<<<< HEAD
At a bare minimum, gelcoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, gelcoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that gelcoind and client programs read from the configuration
=======
At a bare minimum, luxd requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, luxd will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that luxd and client programs read from the configuration
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

<<<<<<< HEAD
If gelcoind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running gelcoind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/gelcoin.conf`.
=======
If luxd is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'

Once you have a password in hand, set rpcpassword= in /etc/lux/lux.conf

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/lux.conf.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

3. Paths
---------------------------------

<<<<<<< HEAD
3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/gelcoind`  
Configuration file:  `/etc/gelcoincore/gelcoin.conf`  
Data directory:      `/var/lib/gelcoind`  
PID file:            `/var/run/gelcoind/gelcoind.pid` (OpenRC and Upstart) or `/var/lib/gelcoind/gelcoind.pid` (systemd)  
Lock file:           `/var/lock/subsys/gelcoind` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the gelcoincore user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
gelcoincore user and group.  Access to gelcoin-cli and other gelcoind rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/gelcoind`  
Configuration file:  `~/Library/Application Support/GelCoinCore/gelcoin.conf`  
Data directory:      `~/Library/Application Support/GelCoinCore`
Lock file:           `~/Library/Application Support/GelCoinCore/.lock`

=======
All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/luxd
Configuration file:  /etc/lux/lux.conf
Data directory:      /var/lib/luxd
PID file:            /var/run/luxd/luxd.pid (OpenRC and Upstart)
                     /var/lib/luxd/luxd.pid (systemd)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the lux user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
lux user and group.  Access to lux-cli and other luxd rpc clients
can then be controlled by group membership.

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
4. Installing Service Configuration
-----------------------------------

4a) systemd

<<<<<<< HEAD
Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start gelcoind` and to enable for system startup run
`systemctl enable gelcoind`

4b) OpenRC

Rename gelcoind.openrc to gelcoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/gelcoind start` and configure it to run on startup with
`rc-update add gelcoind`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop gelcoind.conf in /etc/init.  Test by running `service gelcoind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy gelcoind.init to /etc/init.d/gelcoind. Test by running `service gelcoind start`.

Using this script, you can adjust the path and flags to the gelcoind program by
setting the GELD and FLAGS environment variables in the file
/etc/sysconfig/gelcoind. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.gelcoin.gelcoind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.gelcoin.gelcoind.plist`.

This Launch Agent will cause gelcoind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run gelcoind as the current user.
You will need to modify org.gelcoin.gelcoind.plist if you intend to use it as a
Launch Daemon with a dedicated gelcoincore user.
=======
Installing this .service file consists on just copying it to
/usr/lib/systemd/system directory, followed by the command
"systemctl daemon-reload" in order to update running systemd configuration.

To test, run "systemctl start luxd" and to enable for system startup run
"systemctl enable luxd"

4b) OpenRC

Rename luxd.openrc to luxd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
"/etc/init.d/luxd start" and configure it to run on startup with
"rc-update add luxd"

4c) Upstart (for Debian/Ubuntu based distributions)

Drop luxd.conf in /etc/init.  Test by running "service luxd start"
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon uitility.

4d) CentOS

Copy luxd.init to /etc/init.d/luxd. Test by running "service luxd start".

Using this script, you can adjust the path and flags to the luxd program by
setting the LUXD and FLAGS environment variables in the file
/etc/sysconfig/luxd. You can also use the DAEMONOPTS environment variable here.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
