#@Author: Zeeshan Sajid
#The program itself allows multiple combination of colors and different scales of RGB colors and test them out


// Libraries
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.io.FileInputStream;
import java.io.*;
import javax.swing.*;
import java.awt.Color;

class myGlobal{
    public static int f = 0;
}
class info {
    public String Color;
    public int redVal;
    public int greenVal;
    public int BlueVal;

    public void setColor(String col) {
        Color = col;
    }

    public void setRed(int red) {
        redVal = red;
    }

    public void setGreen(int green) {
        greenVal = green;
    }

    public void setBlue(int blue) {
        BlueVal = blue;
    }
}

class Drawing extends JComponent{
    private Color color = Color.red;
    Color origcol;
    public int red, green, blue;

    public void paint(Graphics canvas)
    {
        Dimension d = getSize();

        canvas.setColor(getColor());
        canvas.fillRect(1, 1, d.width - 2, d.height - 2);
    }

    public Color getColor(){
        return color;
    }
    public void setColor(Color color){
        this.color = color;
        repaint();
    }

    public void setInts()
    {
        red = color.getRed();
        green = color.getGreen();
        blue = color.getBlue();
    }

    public void setOrigcol()
    {
        origcol = this.color;
    }
}

// Main portion of the program. extends the the abstract concept of JFrame.
public class Main extends JFrame {
    protected JButton buttonSave;
    protected JButton buttonReset;
    protected JTextField inputRed;
    protected JTextField inputGreen;
    protected JTextField inputBlue;
    protected JLabel redLabel;
    protected JLabel greenLabel;
    protected JLabel blueLabel;
    protected Graphics canvas;
    protected JList  listColors;
    protected JButton plus;
    protected JButton subtract;
    protected JButton GPlus;
    protected JButton GSubtract;
    protected JButton BPlus;
    protected JButton BSubtract;
    protected Drawing drawCanvas;

    // This uses ListSelectionListener
    private class ListHandler implements ListSelectionListener
    {
        public void valueChanged(ListSelectionEvent e)
        {
            // Set the colors for the different colors in the JFrame
            if ( e.getSource() == listColors )
                if ( !e.getValueIsAdjusting() )
                {
                    if(listColors.getSelectedIndex() == 0)
                    {
                        inputRed.setText("255");
                        inputBlue.setText("0");
                        inputGreen.setText("0");

                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 1)
                    {
                        inputRed.setText("0");
                        inputBlue .setText("0");
                        inputGreen.setText("255");

                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 2)
                    {
                        inputRed.setText("0");
                        inputBlue.setText("255");
                        inputGreen.setText("0");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 3)
                    {
                        inputRed.setText("255");
                        inputBlue.setText("0");
                        inputGreen.setText("255");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 4)
                    {
                        inputRed.setText("0");
                        inputBlue.setText("255");
                        inputGreen.setText("255");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 5)
                    {
                        inputRed.setText("255");
                        inputBlue.setText("255");
                        inputGreen.setText("0");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 6)
                    {
                        inputRed.setText("255");
                        inputBlue.setText("0");
                        inputGreen.setText("100");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 7)
                    {
                        inputRed.setText("255");
                        inputBlue.setText("145");
                        inputGreen.setText("20");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 8)
                    {
                        inputRed.setText("125");
                        inputBlue.setText("125");
                        inputGreen.setText("125");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }
                    if(listColors.getSelectedIndex() == 9)
                    {
                        inputRed.setText("0");
                        inputBlue.setText("0");
                        inputGreen.setText("0");
                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }

                    if(listColors.getSelectedIndex() == 10)
                    {
                        inputRed.setText("255");
                        inputBlue.setText("255");
                        inputGreen.setText("255");

                        drawCanvas.setColor(new Color(Integer.parseInt(inputRed.getText()),Integer.parseInt(inputGreen.getText()),
                                Integer.parseInt(inputBlue.getText())));
                    }
                    if(drawCanvas.origcol != drawCanvas.getColor())
                    {
                        // Name the title of the canvas
                        setTitle("Color Sampler*");
                    }
                }
        }
    }

    private class ActionHandler implements  ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            if(e.getSource() == buttonReset)
            {
                inputRed.setText(Integer.toString(drawCanvas.red));

                inputBlue.setText(Integer.toString(drawCanvas.blue));
                inputGreen.setText(Integer.toString(drawCanvas.green));
                drawCanvas.setColor(new Color(drawCanvas.red,drawCanvas.green, drawCanvas.blue));


                if(drawCanvas.origcol != drawCanvas.getColor())
                {
                    setTitle("Color Sampler");
                }
            }

            else if(e.getSource() == buttonSave){

                drawCanvas.setInts();
                drawCanvas.setOrigcol();

                if(drawCanvas.origcol == drawCanvas.getColor())
                {
                    setTitle("Color Sampler");
                }
            }
        }
    }

    // This implements for the buttons
    private class addHandler implements  ActionListener
    {
        String s;
        int newInput;


        //Color randomColor = new Color(rVal,gVal,bVal);
        public void actionPerformed(ActionEvent e)
        {

            int gVal = Integer.parseInt(inputGreen.getText());
            int rVal = Integer.parseInt(inputRed.getText());
            int bVal = Integer.parseInt(inputBlue.getText());

            // Depending on the button it will subtract the value from the rgb colors and then shows it on the canvas
            if(e.getSource() == GPlus)
            {

                s = inputGreen.getText();
                newInput = Integer.parseInt(s);

                if(newInput != 255)
                {
                    newInput = newInput + 5;

                    System.out.println(newInput);
                    inputGreen.setText(Integer.toString(newInput));

                    gVal = newInput;

                    Color randomColor = new Color(rVal,gVal,bVal);
                    drawCanvas.setColor(new Color(rVal,gVal,bVal));
                    drawCanvas.setInts();
                }
            }

            else if(e.getSource() == GSubtract)
            {
                s = inputGreen.getText();
                newInput = Integer.parseInt(s);


                if(newInput != 0)
                {
                    newInput = newInput - 5;

                    System.out.println(newInput);
                    inputGreen.setText(Integer.toString(newInput));

                    gVal = newInput;

                    Color randomColor = new Color(rVal,gVal,bVal);
                    drawCanvas.setColor(new Color(rVal,gVal,bVal));
                }
            }

            else if(e.getSource() == plus)
            {
                s = inputRed.getText();
                newInput = Integer.parseInt(s);


                if(newInput != 255)
                {
                    newInput = newInput + 5;

                    System.out.println(newInput);
                    inputRed.setText(Integer.toString(newInput));

                    rVal = newInput;

                    Color randomColor = new Color(rVal,gVal,bVal);
                    drawCanvas.setColor(new Color(rVal,gVal,bVal));
                }
            }

            else if(e.getSource() == subtract)
            {
                s = inputRed.getText();
                newInput = Integer.parseInt(s);


                if(newInput != 0)
                {
                    newInput = newInput - 5;

                    System.out.println(newInput);
                    inputRed.setText(Integer.toString(newInput));

                    rVal = newInput;

                    Color randomColor = new Color(rVal,gVal,bVal);
                    drawCanvas.setColor(new Color(rVal,gVal,bVal));
                }
            }

            else if(e.getSource() == BPlus)
            {
                s = inputBlue.getText();
                newInput = Integer.parseInt(s);


                if(newInput != 255)
                {
                    newInput = newInput + 5;

                    System.out.println(newInput);
                    inputBlue.setText(Integer.toString(newInput));

                    bVal = newInput;

                    Color randomColor = new Color(rVal,gVal,bVal);
                    drawCanvas.setColor(new Color(rVal,gVal,bVal));
                }
            }

            else if(e.getSource() == BSubtract)
            {
                s = inputBlue.getText();
                newInput = Integer.parseInt(s);


                if(newInput != 0)
                {
                    newInput = newInput - 5;

                    System.out.println(newInput);
                    inputBlue.setText(Integer.toString(newInput));

                    bVal = newInput;

                    Color randomColor = new Color(rVal,gVal,bVal);
                    drawCanvas.setColor(new Color(rVal,gVal,bVal));
                }
            }

            if(drawCanvas.origcol != drawCanvas.getColor())
            {
                setTitle("Color Sampler*");
            }
        }
    }

    // My own function that calls the JFrame contstructor in which it starts setting up the canvas and buttons
    public Main(String title, info[] stuff) {
        // Call the constructor for JFrame and pass it the string for the window application
        super(title);

        // Set the boundaries for the x and y and it's height and width
        setSize(780, 460);

        setVisible(true);

        // Create canvas
        drawCanvas = new Drawing();
        drawCanvas.setColor(Color.black);
        drawCanvas.setOrigcol();

        // Set the buttons and input fields
        inputRed = new JTextField(" ");
        inputBlue = new JTextField(" ");
        inputGreen = new JTextField(" ");

        // Set labels
        redLabel = new JLabel("Red:");
        greenLabel = new JLabel("Green:");
        blueLabel = new JLabel("Blue:");

        // Set buttons
        subtract = new JButton("-");
        plus = new JButton("+");
        GPlus =  new JButton("+");;
        GSubtract =  new JButton("-");;
        BPlus =  new JButton("+");;
        BSubtract =  new JButton("-");;

        // Get buttons
        buttonSave = new JButton("Save");
        buttonReset = new JButton("Reset");


        // Get button listeners
        buttonReset.addActionListener(new ActionHandler());
        buttonSave.addActionListener(new ActionHandler());

        // Instantiate list
        listColors = new JList();
        listColors.addListSelectionListener(new ListHandler());
        String Colors[] = {stuff[0].Color, stuff[1].Color, stuff[2].Color, stuff[3].Color,
                stuff[4].Color, stuff[5].Color, stuff[6].Color, stuff[7].Color,
                stuff[8].Color, stuff[9].Color,stuff[10].Color};
        listColors.setListData(Colors);

        // Create the layout for the JFrame
        getContentPane().setLayout(null);

        // Start adding the functionalities of the program
        getContentPane().add(inputRed);
        getContentPane().add(inputBlue);
        getContentPane().add(inputGreen);
        getContentPane().add(buttonReset);
        getContentPane().add(buttonSave);
        getContentPane().add(redLabel);
        getContentPane().add(blueLabel);
        getContentPane().add(greenLabel);
        getContentPane().add(subtract);
        getContentPane().add(plus);
        getContentPane().add(GPlus);
        getContentPane().add(GSubtract);
        getContentPane().add(BPlus);
        getContentPane().add(BSubtract);

        // Add drawing canvas
        getContentPane().add(drawCanvas);

        // Add the list portion
        getContentPane().add(listColors);

        // Set the labels for the inputs
        redLabel.setBounds(30, 220,50,30);
        blueLabel.setBounds(30,300,50,30);
        greenLabel.setBounds(20, 260, 50, 30);

        // Get boxes for the inputs
        inputRed.setBounds(60, 220, 50, 30);
        inputGreen.setBounds(60, 260, 50, 30);
        inputBlue.setBounds(60, 300, 50, 30);

        // Button for save and reset
        buttonSave.setBounds(60, 400, 80, 20);
        buttonReset.setBounds(160, 400, 80, 20);

        // Creates a list of colors to be clicked on
        listColors.setBounds(500, 100,200,200);

        // Creates +,- for each of the difference colors
        plus.setBounds(160,220,50,30);
        subtract.setBounds(110,220,50,30);
        plus.addActionListener(new addHandler());
        subtract.addActionListener(new addHandler());

        BPlus.setBounds(160,300,50,30);
        BSubtract.setBounds(110, 300, 50, 30);
        BPlus.addActionListener(new addHandler());
        BSubtract.addActionListener(new addHandler());

        GPlus.setBounds(160,260,50,30);
        GSubtract.setBounds(110, 260, 50, 30);

        GPlus.addActionListener(new addHandler());
        GSubtract.addActionListener(new addHandler());

        // Set the bounds for the canvas
        drawCanvas.setBounds(10,10,270,200);

        // Set the input rgb values to certain colors
        inputRed.setText("0");
        inputGreen.setText("0");
        inputBlue.setText("0");

        // Show the frame and it's content
        setVisible(true);

        // Add a window listener that checks for system.quit() or any other system functions
        addWindowListener(new WindowDestroyer());
    }


    public static void main(String args[]) throws IOException {


        int i = 0; // Looper
        String chunk;
        FileInputStream istream = new FileInputStream("color.txt");
        InputStreamReader fileReader = new InputStreamReader(istream);
        StreamTokenizer token = new StreamTokenizer(fileReader);

        info[] myInfo = new info[11];

        for (i = 0; i < 11; i++) {
            myInfo[i] = new info();
        }

        i = 0;
        while (token.nextToken() != token.TT_EOF) {

            myInfo[i].setColor((String) token.sval);
            token.nextToken();
            myInfo[i].setRed((int) token.nval);
            token.nextToken();
            myInfo[i].setGreen((int) token.nval);
            token.nextToken();
            myInfo[i].setBlue((int) token.nval);

            i++;
        }

        new Main("Color Sampler", myInfo);

        istream.close();
    }


    private class WindowDestroyer extends WindowAdapter {
        public void windowClosing(WindowEvent e) {
            System.exit(0);
        }

    }
}
