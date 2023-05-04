import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import javax.swing.*;
import java.awt.*;




//Servidor definitivo
public class Server {
    private JPanel panelVentana;
    private JLabel labelFila;
    private JTextField textFieldFila;
    private JTextField textFieldCol;
    private JLabel labelColumna;
    private JTextField textFieldVel;
    private JLabel labelVelocidad;
    private JLabel labelEnemigo;
    private JTextField textField2;

    private JButton agregarButton;
    private JButton conectarButton;
    private JButton empezar;
    private JLabel labeljuego1;
    private JLabel labelconectar;
    private JButton conectarButton1;
    private JLabel labelJuego2;
    private JLabel labelConectar2;
    private JButton empezarButton;
    private JLabel bienvenidoAlMenuLabel;

    private JLabel labelOvni;
    private JTextField textOvni;

    public Server() {
        inicializarComponentes();
    }


    private void inicializarComponentes() {
        // Inicializar los componentes
        labelFila = new JLabel("Fila:");
        bienvenidoAlMenuLabel = new JLabel("¡Bienvenido al menú!");
        textFieldFila = new JTextField();
        textFieldCol = new JTextField();
        labelColumna = new JLabel("Columna:");
        textFieldVel = new JTextField();
        labelVelocidad = new JLabel("Velocidad:");
        labelEnemigo = new JLabel("Enemigo:");
        textField2 = new JTextField();
        labelOvni = new JLabel("Ovni:");
        textOvni = new JTextField();
        agregarButton = new JButton("Agregar");
        conectarButton = new JButton("Conectar");
        empezar = new JButton("Empezar");
        labeljuego1 = new JLabel("Juego 1");
        labelconectar = new JLabel("Conectar");
        conectarButton1 = new JButton("Conectar");
        labelJuego2 = new JLabel("Juego 2");
        labelConectar2 = new JLabel("Conectar");
        empezarButton = new JButton("Empezar");
        ImageIcon fondo = new ImageIcon("ruta/de/la/imagen.jpg");


        // Configurar los botones
        agregarButton.addActionListener(e -> {
            // Acción cuando se presiona el botón agregar
        });

        conectarButton.addActionListener(e -> {
            // Acción cuando se presiona el botón conectar
        });

        empezar.addActionListener(e -> {
            // Acción cuando se presiona el botón empezar
        });

        conectarButton1.addActionListener(e -> {
            // Acción cuando se presiona el botón conectar
        });

        empezarButton.addActionListener(e -> {
            // Acción cuando se presiona el botón empezar
        });

        // Configurar el panel principal
        panelVentana = new JPanel(new GridLayout(3, 2, 1, 1));
        panelVentana.add(bienvenidoAlMenuLabel);
        bienvenidoAlMenuLabel.setBounds(250, 50, 200, 20);
        panelVentana.add(labelFila);
        labelFila.setBounds(10, 100, 150, 30);
        panelVentana.add(textFieldFila);
        textFieldFila.setBounds(100, 100, 180, 30);
        panelVentana.add(labelColumna);
        labelColumna.setBounds(10, 170, 180, 30);
        panelVentana.add(textFieldCol);
        textFieldCol.setBounds(100, 170, 180, 30);
        panelVentana.add(labelVelocidad);
        labelVelocidad.setBounds(10, 240, 180, 30);
        panelVentana.add(textFieldVel);
        textFieldVel.setBounds(100, 240, 180, 30);
        panelVentana.add(labelEnemigo);
        labelEnemigo.setBounds(10, 295, 180, 30);
        panelVentana.add(textField2);
        textField2.setBounds(100, 305, 180, 30);
        panelVentana.add(labelOvni);
        labelOvni.setBounds(10, 375, 180, 30);
        panelVentana.add(textOvni);
        textOvni.setBounds(100, 375, 180, 30);
        panelVentana.add(agregarButton);
        agregarButton.setBounds(30, 450, 180, 30);
        panelVentana.add(labeljuego1);
        labeljuego1.setBounds(350, 100, 180, 30);
        panelVentana.add(conectarButton);
        conectarButton.setBounds(350, 125, 180, 30);
        panelVentana.add(labelconectar);
        labelconectar.setBounds(350, 170, 180, 30);
        panelVentana.add(empezar);
        empezar.setBounds(350, 195, 180, 30);
        panelVentana.add(labelJuego2);
        labelJuego2.setBounds(350, 240, 180, 30);
        panelVentana.add(conectarButton1);
        conectarButton1.setBounds(350, 265, 180, 30);
        panelVentana.add(labelConectar2);
        labelConectar2.setBounds(350, 310, 180, 30);
        panelVentana.add(empezarButton);
        empezarButton.setBounds(350, 335, 180, 30);
        panelVentana.setLayout(null);
        panelVentana.setBackground(Color.LIGHT_GRAY);

      
         
    }

    public static void main( String[] args ) throws IOException {
        int puerto = 8080;
        ServerSocket servidor = new ServerSocket(puerto);
        System.out.println("Servidor iniciado en el puerto " + puerto);
        JFrame frame = new JFrame("Menú");
        frame.setContentPane(new Server().panelVentana);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(650, 550); // Establecer el tamaño de la ventana
        frame.setLocationRelativeTo(null); // Centrar la ventana en la pantalla
        frame.setResizable(false);
        frame.setVisible(true);

       

        while (true) {
            Socket cliente = servidor.accept();
            System.out.println("Conexión establecida con el cliente " + cliente.getInetAddress());

            BufferedReader entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
            //System.out.println("Hasta aqui todo bien 1");
            PrintWriter salida = new PrintWriter(cliente.getOutputStream(), true);
            //System.out.println("Hasta aqui todo bien 2");

            // Recibir datos del cliente
            String mensaje = entrada.readLine();
            //System.out.println("Hasta aqui todo bien 3");
            System.out.println("Mensaje del cliente recibido: " + mensaje);

            // Procesar los datos
            String respuesta = "Hola, cliente";
            System.out.println("Respuesta enviada al cliente: " + respuesta);

            // Enviar datos al cliente
            salida.println(respuesta);

            // Cerrar la conexión con el cliente
            cliente.close();
            System.out.println("Conexión cerrada");
        }
    }
}