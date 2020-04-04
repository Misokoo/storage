import java.io.*;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.lang.Object;

/**
 * @brief The ChatServer class is the application entry point, containing the
 *        main. Thus, the application can be run with 'java ChatServer' with an
 *        optional argument to indicate the server listening port. The main
 *        calls either the Server constructor with a default port, or the one
 *        with the port specified as argument.
 */
public class Server {

      public int port;
      public ServerSocket serverSock;

      public Server(int _port) {
            this.port = _port;
            ServerSocket _serverSock = new ServerSocket(_port);
            this.serverSock = _serverSock;
      }

            // compile pas, le prof a ecrit du pseudo code
      public void communication()
      {
            // On attend une connexion sur ce ServerSocket
            Socket sockclient = this.serverSock.accept();

            int MAXBUFF = 1024;
            // On veut lire et ecrire sur cette socket, c'est à dire communiquer 
            try {
                  // 1. lire ce que nous envoie le client
                  BufferedReader fluxEntree = new BufferedReader(new InputStreamReader(sockclient.getInputStream()));
                  // lit au plus MAXBUFF octets
                  byte [] buffer = new byte[MAXBUFF];
                  int nbread = fluxEntree.read(MAXBUFF);
                  // a lu nbread octets
                  // Fabrique une chaine à partir du tableau de bytes
                  System.out.println("Client a dit : " + String(buffer,0,nbread));

                  // 2. écrire au client
                  PrintWriter fluxSortie = new PrintWriter(sockclient.getOutputStream());
                  fluxSortie.write("bien recu...");

            }
            catch (IOException e) {
                  System.err.println("Couldn't get I/O for the connection to: " + hostname);
            }
      }

      public static void main(String[] args) {
            // Server serv;

            // if (args.length==1) {
            // try {
            // int portRequested=Integer.parseInt(args[0]);
            // serv = new Server(portRequested);
            // }
            // catch (NumberFormatException e) {
            // System.err.println("* Error bad port number. Switching to default port");
            // serv = new Server();
            // }
            // }
            // else
            // serv = new Server();
            System.out.println("test Server class");
      }

}