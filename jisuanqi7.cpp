#include "jisuanqi7.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	flag = false;
	buttonFlag = false;
	initUI();
}
void MainWindow::initUI()
{
	QPalette pal = this->palette();
	pal.setColor(QPalette::Window, QColor(0, 0, 0));          //�ֱ����ô��ڵ�ɫ
	this->setPalette(pal);
	mainLayout = new QVBoxLayout;
	widget = new QWidget;
	widget->setLayout(mainLayout);
	setCentralWidget(widget);
	lineEdit = new QLineEdit;
	lineEdit->setFixedHeight(50);
	pal = lineEdit->palette();
	pal.setColor(QPalette::Base, QColor(1, 1, 1));
	pal.setColor(QPalette::Text, QColor(255, 255, 255));
	lineEdit->setPalette(pal);
	lineEdit->setStyleSheet("font-size:40px;");     //���������С
	lineEdit->setAlignment(Qt::AlignRight);         //�����Ҷ���
	QRegExp regExp("[0-9+*/()-.]*");                //������ʽ���涨ֻ������0-9��*��/��+��-��(��)
	QRegExpValidator *validator = new QRegExpValidator(regExp, this);
	lineEdit->setValidator(validator);
	mainLayout->addWidget(lineEdit);
	bottomLayout = new QHBoxLayout;             //��ֱ���ְ�ť
	mainLayout->addLayout(bottomLayout);
	leftLayout = new QVBoxLayout;               //ˮƽ����
	bottomLayout->addLayout(leftLayout);
	rightLayout = new QGridLayout;
	rightLayout->setSpacing(30);                    //���ÿؼ����
	for (int i = 0; i<10; i++)
	{
		digitButtons[i] = createButtons(QString::number(i));                //���Σ���ť�ϴ�����ַ�
		digitButtons[i]->setStyleSheet("font-size:30px;color:white;background-color:rgb(71,71,71)");
	}

	symbolButtons[0] = createButtons("*");
	symbolButtons[1] = createButtons("/");
	symbolButtons[2] = createButtons("+");
	symbolButtons[3] = createButtons("-");
	symbolButtons[4] = createButtons(".");
	symbolButtons[5] = createButtons("=");
	symbolButtons[6] = createButtons("(");
	symbolButtons[7] = createButtons(")");
	symbolButtons[8] = createButtons("CE");
	symbolButtons[9] = createButtons("AC");
	for (int i = 0; i<10; i++)                            //���ð�ť���壬��ɫ����С
	{
		symbolButtons[i]->setStyleSheet("font-weight:bold;font-size:30px;color:white;background-color:rgb(33,33,33)");
	}
	bottomLayout->addLayout(rightLayout);
}
QToolButton *MainWindow::createButtons(const QString &text)                //�����������ť������ֵΪ��ť��ָ��
{
	QToolButton *tb = new QToolButton;
	tb->setText(text);
	connect(tb, SIGNAL(clicked()), this, SLOT(buttonClicked()));           //���������ʱ����ۺ�������ϵ
	tb->setFixedSize(60, 43);
	if (text == QString("0"))
		rightLayout->addWidget(tb, 4, 1);
	else if (text == QString("("))
		rightLayout->addWidget(tb, 0, 0);
	else if (text == QString(")"))
		rightLayout->addWidget(tb, 0, 1);
	else if (text == QString("CE"))
		rightLayout->addWidget(tb, 0, 3);
	else if (text == QString("AC"))
		rightLayout->addWidget(tb, 0, 2);
	else if (text == QString("*"))
		rightLayout->addWidget(tb, 1, 3);
	else if (text == QString("/"))
		rightLayout->addWidget(tb, 2, 3);
	else if (text == QString("+"))
		rightLayout->addWidget(tb, 3, 3);
	else if (text == QString("-"))
		rightLayout->addWidget(tb, 4, 3);
	else if (text == QString("."))
		rightLayout->addWidget(tb, 4, 0);
	else if (text == QString("="))
		rightLayout->addWidget(tb, 4, 2);
	else
		rightLayout->addWidget(tb, (text.toInt() - 1) / 3 + 1, (text.toInt() - 1) % 3);
	return tb;
}
void MainWindow::buttonClicked()
{
	QString expression = lineEdit->text();
	QToolButton *tb = qobject_cast<QToolButton *>(sender());              //"����"����¼�����ߴ���������
	QString text = tb->text();
	if (text == QString("CE"))                                           //��һ��
		lineEdit->backspace();
	else if (text == QString("AC"))                                       //���
		lineEdit->clear();
	else if (text == QString("("))
	{
		lineEdit->cursorBackward(true);                                   //�������
		QString leftLetter = lineEdit->selectedText();
		if (leftLetter == QString("*") || leftLetter == QString("/") || leftLetter == QString("+") || leftLetter == QString("-") || leftLetter==QString(".")||leftLetter == QString(""))                  //�����������ͷ��������(
		{
			pointnumber = 0;
			lineEdit->setText(expression += text);
		}
		else
		{
			lineEdit->setText(expression);
			return;
		}
	}
	else if (text == QString(")"))
	{
		lineEdit->cursorBackward(true);
		QString leftLetter = lineEdit->selectedText();
		int countLeft = expression.count("(");                       //������������������ֹ�����Ϲ涨
		int countRight = expression.count(")");
		if (leftLetter == QString("*") || leftLetter == QString("/") || leftLetter == QString("+") || leftLetter == QString("-") || leftLetter == QString(".") || leftLetter == QString("(") || countLeft <= countRight)
			lineEdit->setText(expression);
		else
		{
			pointnumber = 0;
			lineEdit->setText(expression += text);
		}
	}
	else if (text == QString("*") || text == QString("/") || text == QString("+") || text == QString("-"))
	{
		lineEdit->cursorBackward(true);
		QString leftLetter = lineEdit->selectedText();
		if (leftLetter == QString("*") || leftLetter == QString("/") || leftLetter == QString("+") || leftLetter.isEmpty())
		{
			lineEdit->setText(expression);
		}
		else
		{
			pointnumber = 0;
			lineEdit->setText(expression += text);
		}
	}
	else if (text == QString("."))
	{
		if (pointnumber == 0)
		{
			lineEdit->setText(expression += text);
			pointnumber = 1;
		}
		else if(pointnumber==1)
			lineEdit->setText(expression);
	}
	else if (text == QString("="))                //���ںż���
		calculate();
	else
		lineEdit->setText(expression += text);
}
void MainWindow::calculate()                     //���㺯��
{
	QString expression = lineEdit->text();
	int countLeft = expression.count("(");
	int countRight = expression.count(")");
	if (countRight != countLeft || expression.endsWith('+') || expression.endsWith('-') || expression.endsWith('*') || expression.endsWith('/') || !(expression.contains('+') || expression.contains('-') || expression.contains('*') || expression.contains('/')))
		return;
	QStack<QString> stack;                           //����ջ��׺ת��׺
	QString temp;
	QStringList list;
	while (!expression.isEmpty())
	{
		if (expression.startsWith('+') || expression.startsWith('-') || expression.startsWith('*') || expression.startsWith('/') || expression.startsWith('(') || expression.startsWith(')'))
		{
			if (!temp.isEmpty())                        //��δ�������ݵ�����²������������
			{
				list.append(temp);                      //append�൱��string+=
				temp.clear();
			}
			if (expression.startsWith('+') || expression.startsWith('-') || expression.startsWith(')'))
			{
				while (!stack.isEmpty())
				{
					if (stack.top() == QString('('))
					{
						if (expression.startsWith(')'))
						{
							stackChange.append(QString("pop"));               //����stackChange�۲�ջ��Ԫ�صı仯
							stackChange.append(stack.top());
							stack.pop();                              //������ȡ��ջ��Ԫ�ز�ɾ��
						}
						break;
					}
					else
					{
						stackChange.append(QString("pop"));
						stackChange.append(stack.top());
						list.append(stack.pop());
					}
				}
			}
			if (expression.startsWith(')'))
				expression.remove(0, 1);
			if (!expression.isEmpty())
			{
				stackChange.append(QString("push"));
				stackChange.append(expression.left(1));
				stack.push(expression.left(1));
				expression.remove(0, 1);
			}
		}
		else
		{
			temp += expression.left(1);
			expression.remove(0, 1);
		}
	}
	if (!temp.isEmpty())
		list.append(temp);
	while (!stack.isEmpty())
	{
		stackChange.append(QString("pop"));
		stackChange.append(stack.top());
		list.append(stack.pop());
	}
	qDebug() << list;
	QString operand1;                                  //�����׺
	QString operand2;
	QString result;
	int row = 0;
	while (!list.isEmpty())
	{
		if (list.startsWith("+"))                                     //��ջ��ȡ�����ݽ�����Ӧ���㲢�ѽ������ջ��
		{
			operand2 = stack.pop();
			operand1 = stack.pop();
			result = QString::number(operand1.toDouble() + operand2.toDouble());
			stack.push(result);
		}
		else if (list.startsWith("-"))
		{
			operand2 = stack.pop();
			operand1 = stack.pop();
			result = QString::number(operand1.toDouble() - operand2.toDouble());
			stack.push(result);
		}
		else if (list.startsWith("*"))
		{
			operand2 = stack.pop();
			operand1 = stack.pop();
			result = QString::number(operand1.toDouble()*operand2.toDouble());
			stack.push(result);
		}
		else if (list.startsWith("/"))
		{
			operand2 = stack.pop();
			if (operand2.toDouble() == 0)                         //�Գ���Ϊ0������ʾ
			{
				lineEdit->setText("The divisor cannot be 0");
				flag = true;
			}
			operand1 = stack.pop();
			result = QString::number(operand1.toDouble() / operand2.toDouble());        //��������ַ�������תΪdouble
			stack.push(result);
		}
		else
		{
			stack.push(list.first());
		}
		list.removeFirst();
		operand1.clear();
		operand2.clear();
	}
	lineEdit->setText(result);                      //����������Ϊ��һ�����������
}
