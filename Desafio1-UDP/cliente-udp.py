import socket
HOST = '127.0.0.1' 
PORT = 9999
HOSTE = '127.0.0.2'

udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
dest = (HOST, PORT)
orig = (HOSTE, PORT)
udp.bind(orig);

print 'Para sair use CTRL+C\n'

while True:

    print 'Digite a mensagem a ser enviada\n'
    msgem=raw_input()
    udp.sendto(msgem, dest)
    msg, cliente = udp.recvfrom(1024)
    print cliente, msg


udp.close()
