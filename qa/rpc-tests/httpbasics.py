#!/usr/bin/env python2
<<<<<<< HEAD
# Copyright (c) 2014-2015 The Bitcoin Core developers
=======
# Copyright (c) 2014 The Bitcoin Core developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
<<<<<<< HEAD
# Test rpc http basics
#

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *
=======
# Test REST interface
#

from test_framework import BitcoinTestFramework
from util import *
import base64
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

try:
    import http.client as httplib
except ImportError:
    import httplib
try:
    import urllib.parse as urlparse
except ImportError:
    import urlparse

<<<<<<< HEAD
class HTTPBasicsTest (BitcoinTestFramework):
    def setup_nodes(self):
        return start_nodes(4, self.options.tmpdir)

    def run_test(self):

=======
class HTTPBasicsTest (BitcoinTestFramework):        
    def setup_nodes(self):
        return start_nodes(4, self.options.tmpdir, extra_args=[['-rpckeepalive=1'], ['-rpckeepalive=0'], [], []])

    def run_test(self):        
        
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        #################################################
        # lowlevel check for http persistent connection #
        #################################################
        url = urlparse.urlparse(self.nodes[0].url)
        authpair = url.username + ':' + url.password
<<<<<<< HEAD
        headers = {"Authorization": "Basic " + str_to_b64str(authpair)}

        conn = httplib.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1)
        assert(conn.sock!=None) #according to http/1.1 connection must still be open!

        #send 2nd request without closing connection
        conn.request('POST', '/', '{"method": "getchaintips"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1) #must also response with a correct json-rpc message
        assert(conn.sock!=None) #according to http/1.1 connection must still be open!
        conn.close()

        #same should be if we add keep-alive because this should be the std. behaviour
        headers = {"Authorization": "Basic " + str_to_b64str(authpair), "Connection": "keep-alive"}

        conn = httplib.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1)
        assert(conn.sock!=None) #according to http/1.1 connection must still be open!

        #send 2nd request without closing connection
        conn.request('POST', '/', '{"method": "getchaintips"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1) #must also response with a correct json-rpc message
        assert(conn.sock!=None) #according to http/1.1 connection must still be open!
        conn.close()

        #now do the same with "Connection: close"
        headers = {"Authorization": "Basic " + str_to_b64str(authpair), "Connection":"close"}

        conn = httplib.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1)
        assert(conn.sock==None) #now the connection must be closed after the response

        #node1 (2nd node) is running with disabled keep-alive option
        urlNode1 = urlparse.urlparse(self.nodes[1].url)
        authpair = urlNode1.username + ':' + urlNode1.password
        headers = {"Authorization": "Basic " + str_to_b64str(authpair)}

        conn = httplib.HTTPConnection(urlNode1.hostname, urlNode1.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1)

        #node2 (third node) is running with standard keep-alive parameters which means keep-alive is on
        urlNode2 = urlparse.urlparse(self.nodes[2].url)
        authpair = urlNode2.username + ':' + urlNode2.password
        headers = {"Authorization": "Basic " + str_to_b64str(authpair)}

        conn = httplib.HTTPConnection(urlNode2.hostname, urlNode2.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read()
        assert(b'"error":null' in out1)
        assert(conn.sock!=None) #connection must be closed because bitcoind should use keep-alive by default

        # Check excessive request size
        conn = httplib.HTTPConnection(urlNode2.hostname, urlNode2.port)
        conn.connect()
        conn.request('GET', '/' + ('x'*1000), '', headers)
        out1 = conn.getresponse()
        assert_equal(out1.status, httplib.NOT_FOUND)

        conn = httplib.HTTPConnection(urlNode2.hostname, urlNode2.port)
        conn.connect()
        conn.request('GET', '/' + ('x'*10000), '', headers)
        out1 = conn.getresponse()
        assert_equal(out1.status, httplib.BAD_REQUEST)


=======
        headers = {"Authorization": "Basic " + base64.b64encode(authpair)}
        
        conn = httplib.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True)
        assert_equal(conn.sock!=None, True) #according to http/1.1 connection must still be open!
        
        #send 2nd request without closing connection
        conn.request('POST', '/', '{"method": "getchaintips"}', headers)
        out2 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True) #must also response with a correct json-rpc message
        assert_equal(conn.sock!=None, True) #according to http/1.1 connection must still be open!
        conn.close()
        
        #same should be if we add keep-alive because this should be the std. behaviour
        headers = {"Authorization": "Basic " + base64.b64encode(authpair), "Connection": "keep-alive"}
        
        conn = httplib.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True)
        assert_equal(conn.sock!=None, True) #according to http/1.1 connection must still be open!
        
        #send 2nd request without closing connection
        conn.request('POST', '/', '{"method": "getchaintips"}', headers)
        out2 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True) #must also response with a correct json-rpc message
        assert_equal(conn.sock!=None, True) #according to http/1.1 connection must still be open!
        conn.close()
        
        #now do the same with "Connection: close"
        headers = {"Authorization": "Basic " + base64.b64encode(authpair), "Connection":"close"}
        
        conn = httplib.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True)
        assert_equal(conn.sock!=None, False) #now the connection must be closed after the response        
        
        #node1 (2nd node) is running with disabled keep-alive option
        urlNode1 = urlparse.urlparse(self.nodes[1].url)
        authpair = urlNode1.username + ':' + urlNode1.password
        headers = {"Authorization": "Basic " + base64.b64encode(authpair)}
                
        conn = httplib.HTTPConnection(urlNode1.hostname, urlNode1.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True)
        assert_equal(conn.sock!=None, False) #connection must be closed because keep-alive was set to false
        
        #node2 (third node) is running with standard keep-alive parameters which means keep-alive is off
        urlNode2 = urlparse.urlparse(self.nodes[2].url)
        authpair = urlNode2.username + ':' + urlNode2.password
        headers = {"Authorization": "Basic " + base64.b64encode(authpair)}
                
        conn = httplib.HTTPConnection(urlNode2.hostname, urlNode2.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        out1 = conn.getresponse().read();
        assert_equal('"error":null' in out1, True)
        assert_equal(conn.sock!=None, True) #connection must be closed because bitcoind should use keep-alive by default
        
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
if __name__ == '__main__':
    HTTPBasicsTest ().main ()
