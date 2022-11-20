#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
using namespace std;
/*
 *Author:yuzewei
 *email:salanderyzw@163.com
 *Date:2020/10/24
*/

const int popSize = 20;     //种群大小
const int len = 4;          //染色体长度
const double Pc = 0.7;      //交叉概率
const double Pm = 0.001;    //变异概率
const int generation = 20;  //迭代次数（终止条件）

typedef struct individual   //个体结构体
{
    bool chromo1[len];      //染色体x1
    bool chromo2[len];      //染色体x2
    double fit;             //适应度
    double prob;            //选中概率
}individual;
struct individual pop[popSize];         //种群
struct individual nextPop[popSize];     //下一代种群
int nextPopNum = 0;                     //记录当前下一代种群中个体数
double lineProb[popSize];               //线性选择概率（用于轮盘赌）
double totalFit;            //总适应度
int gen = 1;                //当前代数

double getXValue(bool[]);
double getFitness(individual);
double getProb(individual);
int getRanChromo();
void getInitPop(struct individual []);
bool inLegality(individual);
void selection(struct individual[]);
void crossover(struct individual[]);
void evolution();
void popPrintf(struct individual[]);

int main()
{
    srand((unsigned)time(NULL));

    getInitPop(pop);
    while (gen < generation)
        evolution();

    cout << "最优解为：f(" << getXValue(pop[0].chromo1) << "," << getXValue(pop[0].chromo2) << ")="
         << pow(getXValue(pop[0].chromo1),2) + pow(getXValue(pop[0].chromo2), 2) <<endl;

    return 0;
}

/*获取二进制编码对应的x值*/
double getXValue(bool ch[len])
{
    double x;
    x = ch[0] * 8.0 + ch[1] * 4.0 + ch[2] * 2.0 + ch[3] * 1.0;
    return x;
}

/*获取个体适应度*/
double getFitness(individual in)
{
    double x1, x2;
    double fit = 0;
    x1 = getXValue(in.chromo1);
    x2 = getXValue(in.chromo2);
    if (x1 == 0 && x2 == 0)
        return 0;
    else
        fit = 1 / (pow(x1, 2) + pow(x2, 2));   //值越小，适应度越高，用1/f(x)表示适应度
    return fit;
}

/*获取个体选择概率*/
double getProb(individual in)
{
    double prob = 0;
    prob = in.fit / totalFit;
    return prob;
}

/*随机获取x的值（0 ~ 10）*/
int getRanChromo()
{
    int ch = 0;
    ch = rand() % 10;  //获取0~10之间的随机数
    return ch;
}

/*获取总适应度*/
double getTotalFit(struct individual pop[])
{
    double totalFit = 0;
    for (int i = 0; i < popSize; i++)
        totalFit += pop[i].fit;
    return totalFit;
}

/*获取初始种群*/
void getInitPop(struct individual pop[])
{
    int ch1, ch2;
    ch1 = ch2 = 0;
    totalFit = 0;
    for (int i = 0; i < popSize; i++)
    {
        ch1 = getRanChromo();
        ch2 = getRanChromo();
        for (int j = len; j > 0; j--)
        {
            pop[i].chromo1[len - j] = floor(ch1 / pow(2, j - 1));
            ch1 = ch1 % (int)pow(2, j - 1);
            pop[i].chromo2[len - j] = floor(ch2 / pow(2, j - 1));
            ch2 = ch2 % (int)pow(2, j - 1);
        }
        pop[i].fit = getFitness(pop[i]);
    }
    totalFit = getTotalFit(pop);
    for (int i = 0; i < popSize; i++)
    {
        pop[i].prob = getProb(pop[i]);
    }
    //打印初始种群
    cout << "第1代种群：" << endl;
    popPrintf(pop);
}

/*判断（杂交与变异所得）个体值是否符合要求*/
bool inLegality(individual in)
{
    double x1, x2;
    x1 = getXValue(in.chromo1);
    x2 = getXValue(in.chromo2);
    if (x1 > 10 || x2 > 10)
        return 0;
    else
        return 1;
}

/*选择(轮盘式)*/
void selection(struct individual pop[])
{
    cout << "  选择一次" << endl;
    lineProb[0] = pop[0].prob;
    for (int i = 1; i < popSize; i++)//累计概率，使种群内个体的概率线性化
    {
        lineProb[i] = lineProb[i-1] + pop[i].prob;
    }
    double r = rand() / double(RAND_MAX);//获取0~1之间随机数
    //cout << "轮盘赌随机数：" << r << endl;
    for (int j = 0; j < popSize; j++)//查询随机数对应的轮盘上的个体
    {
        if ( r <= lineProb[j])
        {
            nextPop[nextPopNum] = pop[j];
            nextPopNum++;
            break;
        }
    }
}

/*交叉*/
void crossover(struct individual pop[])
{
    double r1;
    int r2, r3, r4;
    bool a, b;
    r1 = rand() / double(RAND_MAX);//获取0~1之间随机数
    if (r1 <= Pc)
    {
        r2 = (rand() % (popSize));
        r3 = (rand() % (popSize));
        r4 = (rand() % (len));

        if (nextPopNum + 1 > popSize - 1)//当前新种群只剩一个位置
        {
            cout << "  交叉一次，产生一个新个体" << endl;
            nextPop[nextPopNum] = pop[r2];
            for (int i = r4; i < len; i++)
            {
                nextPop[nextPopNum].chromo1[i] = pop[r3].chromo1[i];
                nextPop[nextPopNum].chromo2[i] = pop[r3].chromo2[i];
            }
            nextPop[nextPopNum].fit = getFitness(nextPop[nextPopNum]); //更新个体适应度
            if (inLegality(nextPop[nextPopNum])) //判断新个体值是否合法
                nextPopNum++;
            else
                nextPopNum--;
        }
        else //新种群中剩余空位大于等于2
        {
            cout << "  交叉一次，产生二个新个体" << endl;
            nextPop[nextPopNum] = pop[r2];
            nextPopNum++;
            nextPop[nextPopNum] = pop[r3];

            //两个个体进行杂交
            for (int i = r4; i < len; i++)
            {
                a = nextPop[nextPopNum - 1].chromo1[i];
                nextPop[nextPopNum - 1].chromo1[i] = nextPop[nextPopNum].chromo1[i];
                nextPop[nextPopNum].chromo1[i] = a;

                b = nextPop[nextPopNum - 1].chromo2[i];
                nextPop[nextPopNum - 1].chromo2[i] = nextPop[nextPopNum].chromo2[i];
                nextPop[nextPopNum].chromo2[i] = b;
            }
            //更新适应度
            nextPop[nextPopNum - 1].fit = getFitness(nextPop[nextPopNum - 1]);
            nextPop[nextPopNum].fit = getFitness(nextPop[nextPopNum]);

            //判断新个体值是否合法
            if (!inLegality(nextPop[nextPopNum - 1]))
            {
                if(!inLegality(nextPop[nextPopNum]))
                    nextPopNum --;
                else
                    nextPop[nextPopNum - 1] = nextPop[nextPopNum];
            }
            else
            {
                if (inLegality(nextPop[nextPopNum]))
                    nextPopNum++;
            }
        }
    }
    else
        cout << "  此次未进行交叉" << endl;

}

/*变异*/
void mutataion(struct individual pop[])
{
    double m1;
    int m2, m3;
    m1 = rand() / double(RAND_MAX);//获取0~1之间随机数
    if (m1 < Pm)
    {
        cout << "  变异一次，产生一个新个体" << endl;
        m2 = (rand() % (popSize));
        m3 = (rand() % (len));
        nextPop[nextPopNum] = pop[m2];

        //取反
        if (nextPop[nextPopNum].chromo1[m3] == 1)
            nextPop[nextPopNum].chromo1[m3] = 0;
        else
            nextPop[nextPopNum].chromo1[m3] = 1;

        //判断新个体值是否合法
        if (inLegality(nextPop[nextPopNum]))
            nextPopNum++;
        else
            nextPopNum--;
    }
    else
        cout << "  此次未进行变异" << endl;
}

/*进化*/
void evolution()
{
    gen++;
    cout << "第" << gen << "代种群：" << endl;
    //遗传操作
    while (nextPopNum < popSize)
    {
        selection(pop);
        if (nextPopNum == popSize) break;
        crossover(pop);
        if (nextPopNum == popSize) break;
        mutataion(pop);
        if (nextPopNum == popSize) break;
    }
    //更新选择概率
    totalFit = getTotalFit(nextPop);
    for (int i = 0; i < popSize; i++)
        nextPop[i].prob = getProb(nextPop[i]);

    //打印新种群
    popPrintf(nextPop);

    //更新种群存储空间
    for (int i = 0; i < popSize; i++)
        pop[i] = nextPop[i];
    nextPopNum = 0;

}

/*打印种群*/
void popPrintf(struct individual pop[])
{
    for (int i = 0; i < popSize; i++)
    {
        for (int j = 0; j < len; j++)
            cout << pop[i].chromo1[j];
        cout << " ";
        for (int j = 0; j < len; j++)
            cout << pop[i].chromo2[j];
        cout << " ";
        cout << setw(10) << left<< pop[i].fit;
        cout << " ";
        cout << pop[i].prob;
        cout << endl;
    }
}

