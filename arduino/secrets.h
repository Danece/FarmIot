#include <pgmspace.h>
#define THINGNAME "Esp32_board"
const char AWS_IOT_ENDPOINT[] = "a3fch6a2ycw2yu-ats.iot.us-east-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUalPRnhk60zDP0ODfraWeA1jWqEYwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDUwODA5MDYz
MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALAtyfLlXqjbMx6X9ry9
RLchvFcu/DmkmVKO3spGRSvURshntFArIuBeOf7+YZvsThrAdtUBZ9mfmFRv0WQ7
6rgUjGfiNe/pVvLvA+x8c6Depcer383mpspjQUmBAhc8NMRm2VhhzJzCOOb21sPL
E6lIQ8EAzz8iOZGXhI/TVbJyx8IdiSRVjVRU7vDAhkrLxoDzrYBl2bQ4awiGY4/x
VVOdXfdSrNYBAgl/43m1jpKhHQjAs8WkyliioMQ2HU/pGIyUiqiEsRzQ0nZUaw2d
VN7eY5jS9Btg3DsElEWP5YnnB/Z6R8syBtk7n+419apmXk4J69PygPg8mVLg/tYZ
wQkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUgxcr0cn7rkMHprQM1XMHNR+P7qkwHQYD
VR0OBBYEFJQ+w6nhvESfKgPimjjZrOwqMDvfMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAxl0/eZvRrRVfT0TvCbDNDBNqN
lrDK/5ycv3Dd/glIjl/5spOG8wdeR5imVO6eA2cWRn8Wq9f9Sl0WV7Jg4sJhe7fW
8r4u4brB0yuaKsuCjoP7zcKjoaOVGcImXMhN7+Qj/10J8HPgdDSqAL3BqXPxfVnu
x4WqMbcuvy+EOdC4XMux/HZtv3/t/tEIkVM2pGvoNLu/hp88hTL3uZXsuWbr9ksa
O17YVYaujDRzVIBBWbK5CXJxG+4k//ct0wT3ieB/v2E9k+04TIwg03+/tQFnudXQ
genUNTfkGOqWBUswoQ+koJblYOr12HQM9Cu2z0rgkWlD0KY/xFkEBfLJQpGX
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAsC3J8uVeqNszHpf2vL1EtyG8Vy78OaSZUo7eykZFK9RGyGe0
UCsi4F45/v5hm+xOGsB21QFn2Z+YVG/RZDvquBSMZ+I17+lW8u8D7HxzoN6lx6vf
zeamymNBSYECFzw0xGbZWGHMnMI45vbWw8sTqUhDwQDPPyI5kZeEj9NVsnLHwh2J
JFWNVFTu8MCGSsvGgPOtgGXZtDhrCIZjj/FVU51d91Ks1gECCX/jebWOkqEdCMCz
xaTKWKKgxDYdT+kYjJSKqISxHNDSdlRrDZ1U3t5jmNL0G2DcOwSURY/liecH9npH
yzIG2Tuf7jX1qmZeTgnr0/KA+DyZUuD+1hnBCQIDAQABAoIBAQCZDJ4ksZfjLtGg
4TkKy413XgpE3t9koBZF/zGSHSuYIMgA7v5YqrCYo6LUX16iWs2bNdnFv3vdNWTa
7WzFG7wTgF5dHMnoihfr4THSbmbwuJrh8/Dv6VC5/zHHThhn4PiiKgrkWcmr4JoY
IxV9b9y7sbiSYUapPO0wCqWxYFFRPC2jWhQF4pkm/d2TT4fQyJd2AlCe4xWf0/ZX
qtbJovHTSFG59Rhh41xcT29YoDk5y2gHLJcLEWauJDTAWnE1BY/8lSthW+nQJTUs
e1tBPh3bLl3iee6/b3CEGz7jk/w6ZRZoSiWS0GGtU9kwKLPcfZB20JjMMhPgsrER
CI2Sci9lAoGBAOFhGOZfRP+IvzA2Ovg1DHDG0B/V96weT/grzTdnWsgd5XmV/j71
4wR+WLwx1SKHVBKmtoFj7bgMXXipOcUCQ0qiwh9OaKxxoE5NMYdE929FdltFzzej
Yop1aGfcXbOgdKHOl3MBhkEdv8wqLos5a3WAooq31XEChcZHDZFFWE6nAoGBAMgd
dGwFOP2pTtUciB841PUfDh2cmbYE6SmxLaOeqcpEWEc4p7dyjmbxfXFtkX/6I6/a
IByhDQ83IxUi+H0ovcebzV/aHo7Yp1b1aRctHdBer3a9yiTTn18LDQABD9eslcvm
tgrDnCGdjEzUb+7CZYWcsDYLC5ogDP8j5uUp6ZjPAoGBAI5Ar+uwFCfJkwsGH6BM
M2b3RaPidGnx0/3K/8NJe/Y1UIK2lnv8zOYoLS/TsDgT/I+tJCJ1BTUWsOSYwzrC
2+A+7JG/9rdpHIpvlKRRdm+IA1VGsazndin4QwbTA11+GD+M2vCe9LMi6M0fjrMX
cej/YRh3QcQLmI32iOy5PSyfAoGBAISxA0GdNOz+Fwe4o4oQZSUkMnfwHvxSxUif
82NLEcrNBrwzFQLPMx2Pg15zCMeTVZaFTEWvhLlSFjEtvxc+rJhu9v9X4mtVvaAr
mkOD5wEDx9U0g5VnvYWIDlayXY7lIW7SzGLW0fB4R0+qjY4D2M1/2Ff9evP3zKZh
Z/kMkZiBAoGAS8Q7zaxwVq3bP92rSfL0OiEAa+jzDQ0XCl5PH/M3m7s06Ql3jiIw
8QwI7ViWM6UlkVhmpzaNg+G50BVnG+FpvaIid5Ahlo3b6DgcoO2kZHAFQmpbaPyJ
rocRTLbH43KXzITNfvxgTrrklD4KvL1esQoioQMUhEUccC0x2znwlAs=
-----END RSA PRIVATE KEY-----
)KEY";
