#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


const int Population_size = 100;
const int Chromosome_length = 6;
double rate_crossover = 0.5;
double rate_mutation = 0.001;
int iteration_num = 50;


//将染色体定义为结构体类型
typedef struct Chromosome
{
    short int bit[Chromosome_length];
    double value;
    double fitness;
    double rate_fit;
    double cumu_fit;
}chromosome;

void population_initialize(chromosome (&population_current)[Population_size]);

void decode(chromosome &population_current) ;

double objective_function(double x);

void fresh_property(chromosome(&population_current)[Population_size]);

void seletc_prw(chromosome(&population_current)[Population_size], chromosome(&population_next_generation)[Population_size], chromosome &best_individual);

void crossover(chromosome (&population_next_generation)[Population_size]);

void mutation(chromosome (&population_next_generation)[Population_size]);


void main()
{

    clock_t start, end;//开始计时,精确到秒
    start = clock();



    chromosome population_current[Population_size];                    //当前种群
    chromosome population_next_generation[Population_size];       //产生的下一代的种群
    chromosome best_individual;                                                 //记录适应度的最大值
    chromosome zeros_chromosome;                                                //定义一个全为0的个体，用于群体中某个个体的重置


    int i = 0,j = 0;

    for (i = 0; i < Chromosome_length; i++)
        zeros_chromosome.bit[i] = 0;
    zeros_chromosome.fitness = 0.0;
    zeros_chromosome.value = 0.0;
    zeros_chromosome.rate_fit = 0.0;
    zeros_chromosome.cumu_fit = 0.0;

    best_individual = zeros_chromosome;
    for (i = 0; i < Population_size; i++)
    {
        population_current[i] = zeros_chromosome;
        population_next_generation[i] = zeros_chromosome;
    }



    printf("\nWelcome to the Genetic Algorithm！\n");  //
    printf("The Algorithm is based on the function y = -x^2 + 5 to find the maximum value of the function.\n");

    enter:printf("\nPlease enter the no. of iterations\n请输入您要设定的迭代数 : ");
    scanf_s("%d", &iteration_num);


    if (iteration_num <1)
        goto enter;



    population_initialize(population_current);

    fresh_property(population_current);

    for (i = 0; i< iteration_num; i++)
    {
        seletc_prw(population_current,population_next_generation,best_individual);
        crossover(population_next_generation);
        mutation(population_next_generation);
        fresh_property(population_next_generation);
        for (i = 0; i < Population_size; i++)
        {
            population_current[i] = population_next_generation[i];
            population_next_generation[i] = zeros_chromosome;
        }
        //检验时间是否到90s
        end = clock();
        if (double(end - start) / CLK_TCK> 89)
            break;
    }
    //输出所用时间
    printf("\n 迭代%d次所用时间为： %f\n", iteration_num, double(end - start) / CLK_TCK);

    //输出结果
    printf("\n 函数得到最大值为： %f ,适应度为：%f \n", best_individual.value, best_individual.fitness);

    for (i = 0; i<Population_size; i++)
    {
        printf(" population_current[%d]=", i);
        for (j = 0; j < Chromosome_length; j++)
            printf(" %d", population_current[i].bit[j]);
        printf("        value=%f    fitness = %f\n", population_current[i].value, population_current[i].fitness);
    }
    printf("\nPress any key to end ! ");


    system("pause");
}


void population_initialize(chromosome (&population_current)[Population_size])
{
    int i = 0, j = 0;

    srand((unsigned)time(NULL));

    for (j = 0; j<Population_size; j++)
    {
        for (i = 0; i<Chromosome_length; i++)
        {
            population_current[j].bit[i] = rand()% 2;
        }

    }

}


void decode(chromosome &population_current)
{//此处的染色体长度为，其中个表示符号位
    int i = 0;
    population_current.value = 0;
    //地位在前，高位再后
    for( i = 0 ; i < Chromosome_length -1; i++ )
        population_current.value += (double)pow(2, i) * (double)population_current.bit[i];    //遍历染色体二进制编码,
    //最高位为符号位，如果是1代表负数
    if (population_current.bit[Chromosome_length - 1] == 1)
        population_current.value = 0 - population_current.value;

}

//函数:计算适应度
double objective_function(double x)
{
    double y;
    // 目标函数：y= - ( (x-1)^ 2 ) +5
    y = -((x - 1) *(x - 1)) + 5;
    return(y);
}

void fresh_property(chromosome (&population_current)[Population_size])
{
    int j = 0;
    double sum = 0;

    for (j = 0; j < Population_size; j++)
    {
        decode(population_current[j]);
        population_current[j].fitness = objective_function(population_current[j].value);
        sum = sum + population_current[j].fitness;

    }

    population_current[0].rate_fit = population_current[0].fitness / sum;
    population_current[0].cumu_fit = population_current[0].rate_fit;
    for (j = 1; j < Population_size; j++)
    {
        population_current[j].rate_fit = population_current[j].fitness / sum;
        population_current[j].cumu_fit = population_current[j].rate_fit + population_current[j-1].cumu_fit;
    }


}

void seletc_prw(chromosome (&population_current)[Population_size],chromosome (&population_next_generation)[Population_size],chromosome &best_individual)
{

    int i = 0, j = 0;
    double rate_rand = 0.0;
    best_individual = population_current[0];
    //产生随机数种子
    srand((unsigned)time(NULL));
    for (i = 0; i < Population_size; i++)
    {
        rate_rand = (float)rand() / (RAND_MAX);
        if (rate_rand < population_current[0].cumu_fit)
            population_next_generation[i] = population_current[0];
        else
        {
            for (j = 0; j < Population_size; j++)
            {
                if (population_current[j].cumu_fit <= rate_rand && rate_rand < population_current[j + 1].cumu_fit)
                {
                    population_next_generation[i] = population_current[j + 1];
                    break;
                }
            }
        }

        //如果当前个体比目前的最有个体还要优秀，则将当前个体设为最优个体
        if(population_current[i].fitness > best_individual.fitness)
            best_individual = population_current[i];
    }

}


void crossover(chromosome (&population_next_generation)[Population_size])
{
    int i = 0,j = 0;
    double rate_rand = 0.0;
    short int bit_temp = 0;
    int num1_rand = 0, num2_rand = 0, position_rand = 0;
    //产生随机数种子
    srand((unsigned)time(NULL));
    //应当交叉变异多少次呢？先设定为种群数量
    for (j = 0; j<Population_size; j++)
    {
        rate_rand = (float)rand()/(RAND_MAX);
        //如果大于交叉概率就进行交叉操作
        if(rate_rand <= rate_crossover)
        {
            //随机产生两个染色体
            num1_rand = (int)rand()%(Population_size);
            num2_rand = (int)rand()%(Population_size);
            //随机产生两个染色体的交叉位置
            position_rand = (int)rand()%(Chromosome_length - 1);
            //采用单点交叉，交叉点之后的位数交换
            for (i = position_rand; i<Chromosome_length; i++)
            {
                bit_temp = population_next_generation[num1_rand].bit[i];
                population_next_generation[num1_rand].bit[i] = population_next_generation[num2_rand].bit[i];
                population_next_generation[num2_rand].bit[i] = bit_temp;
            }

        }
    }

}

// 函数：变异操作
void mutation(chromosome (&population_next_generation)[Population_size])
{
    int position_rand = 0;
    int i = 0;
    double rate_rand = 0.0;
    //产生随机数种子
    srand((unsigned)time(NULL));
    //变异次数设定为种群数量
    for (i = 0; i<Population_size; i++)
    {
        rate_rand = (float)rand()/(RAND_MAX);
        //如果大于交叉概率就进行变异操作
        if(rate_rand <= rate_mutation)
        {
            //随机产生突变位置
            position_rand = (int)rand()%(Chromosome_length);
            //突变
            if (population_next_generation[i].bit[position_rand] == 0)
                population_next_generation[i].bit[position_rand] = 1;
            else
                population_next_generation[i].bit[position_rand] = 0;

        }

    }
}