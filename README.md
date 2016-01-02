# MediaTekLinkitSmart7688Duo

Author - Jancsi Wang - JancsiWang@Gmail.com 
@20160103

arduino controls the following componets:
1. OLED display - I2c
2. Light sensor - A0
3. Solid moisture sensor - A2
4. DHT11 - temperture and humid sensor - D4
*5. A relay controller -  D7. gpio0 in MPU side.

send data to MPU via Serial1


app.js
1. read data from /dev/ttyS0 and send to MCS
2. read Relay_Control signal and pull up/down gpio0
