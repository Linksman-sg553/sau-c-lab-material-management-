#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
typedef struct Material
{
    char id[1001], name[1001], pro[1001];//id代表编号， name代表材料名称， pro代表保管人
    double in, out, pri;//in代表入库数， out代表出库数， pri代表单价
    int iny, inm, ind;
    int outy, outm, outd;
    //以上代表进出货时间，排序年月日时分秒；
    char note[10001];//备注
    struct Material *next;//链表
}ma;//用 ma 来表示
void Filecount()
{
    FILE *fpc, *fpd;
    fpd = fopen("data.txt", "r");
    int i = 0;
    char ids[101], names[101], pros[101], notes[10101];
    int inys, inms, inds;//进货年月日
    int outys, outms, outds;//出货年月日
    double ins, outs, pris;
    while(!feof(fpd))
    {
        fscanf(fpd, "%s %s %s %lf %lf %lf %d.%d.%d %d.%d.%d %s", ids, names, pros, &ins, &outs, &pris, &inys, &inms, &inds, &outys, &outms, &outds, notes);
        i++;
    }
    i--;
    fclose(fpd);
    fpc = fopen("count.txt", "w");
    fprintf(fpc, "%d", i);
    fclose(fpc);
}
void Filew(ma *head)//1.写 2.加
{
    FILE *fp;
    fp = fopen("data.txt", "w");
    ma *p;
    p = head->next;
    while(p)
    {
        fprintf(fp, "%s %s %s %lf %lf %lf %d.%d.%d %d.%d.%d %s\n", p->id, p->name, p->pro, p->in, p->out, p->pri, p->iny, p->inm, p->ind, p->outy, p->outm, p->outd, p->note);
        p = p->next;
    }
    fclose(fp);
}
ma *Createlink(int *n)
{
    puts("输入形式：编号 名称 保管人 入库数 出库数 单价 入库时间 出库时间 备注(不可为空) //时间输入格式：年.月.日 例如 2019.5.31");
    int ai = 0;
    puts("***输入请以编号为“end~”结束***");
    ma *p1, *p2, *head;
    head = (ma *)malloc(sizeof(ma));
    head->next = NULL;
    char ids[101], names[101], pros[101], notes[10101];
    int inys, inms, inds, flag = 1, flags = 1;
    int outys, outms, outds;
    double ins, outs, pris;
    scanf("%s", ids);
    if(strcmp(ids,"end~") == 0)
    {
        FILE *fp;
        fp = fopen("data.txt", "w");
        fclose(fp);
        p1 = (ma *)malloc(sizeof(ma));
        strcpy(p1->id, "\0");
        strcpy(p1->name, "\0");
        strcpy(p1->pro, "\0");
        strcpy(p1->note, "\0");
        p1->iny = '\0';
        p1->inm = '\0';
        p1->ind = '\0';
        p1->outy = '\0';
        p1->outm = '\0';
        p1->outd = '\0';
        p1->in = '\0';
        p1->out = '\0';
        p1->pri = '\0';
        p1->next = '\0';
        head->next = p1;
        ai = flag = 0;
    }

    if(flag == 1)
    {
        scanf("%s %s %lf %lf %lf %d.%d.%d %d.%d.%d %s", names, pros, &ins, &outs, &pris, &inys, &inms, &inds, &outys, &outms, &outds, notes);
        do{
            ai++;
            p1 = (ma *)malloc(sizeof(ma));
            strcpy(p1->id, ids);
            strcpy(p1->name, names);
            strcpy(p1->pro, pros);
            strcpy(p1->note, notes);
            p1->iny = inys;
            p1->inm = inms;
            p1->ind = inds;
            p1->outy = outys;
            p1->outm = outms;
            p1->outd = outds;
            p1->in = ins;
            p1->out = outs;
            p1->pri = pris;
            p1->next = NULL;
            if(head->next == NULL)
                head->next = p1;
            else
                p2->next = p1;
            p2 = p1;
            while(flags)
            {
                scanf("%s", ids);
                if(strcmp(ids,"end~") == 0)
                    break;
                scanf("%s %s %lf %lf %lf %d.%d.%d %d.%d.%d %s", names, pros, &ins, &outs, &pris, &inys, &inms, &inds, &outys, &outms, &outds, notes);
                ma *q = head->next;
                while(q)
                {
                    if(strcmp(q->id, ids) == 0)
                    {
                        puts("-----输入编号已存在，不可重复，上一条作废-----");
                        flags = 1;
                        break;
                    }
                    else
                    {
                        flags = 0;
                        q = q->next;
                    }
                }
            }
            flags = 1;
            if(strcmp(ids,"end~") == 0)
                break;
        }while(strcmp(ids,"end~") != 0);
    }
    *n = ai;
    Filew(head);
    return head;
}
void show(ma *p)
{
    printf("编号：%s 名称：%s 保管人：%s 入库数：%.4lf 出库数：%.4lf 单价：%.2lf 入库时间：%d.%d.%d 出库时间：%d.%d.%d 备注: %s\n", p->id, p->name, p->pro, p->in, p->out, p->pri, p->iny, p->inm, p->ind, p->outy, p->outm, p->outd, p->note);
}
void Display(ma *head, int *n)
{
    if(*n == 0)
        puts("无任何内容，请按'a'添加信息");
    else
    {
        ma *p;
        p = head->next;
        while(p)
        {
            show(p);
            p = p->next;
        }
    }
}
int Find(ma *head, int *n)
{
    if(*n == 0)
        puts("-----无任何内容，请按'a'添加信息-----");
    else
    {
        char ch, s[101];
        double cs;
        int ay, am, ad, flag = 0;
        ma *p = head->next;
        puts("-----查找类型：-----");
        puts("      1.编号        ");
        puts("      2.名称        ");
        puts("      3.保管人      ");
        puts("      4.单价        ");
        puts("      5.入库时间    ");
        puts("      6.出库时间    ");
        puts("put 1~6 please");
        ch = getch();
        switch(ch)
        {
        case'1':
            puts("-----please input-----:");
            scanf("%s", s);
            while(p)
            {
                if(strcmp(p->id, s) == 0)
                {
                    flag = 1;
                    show(p);
                }
                p = p->next;
            }
            break;
        case'2':
            puts("-----please input-----:");
            scanf("%s", s);
            while(p)
            {
                if(strcmp(p->name, s) == 0)
                {
                    flag = 1;
                    show(p);
                }
                p = p->next;
            }
            break;
        case'3':
            puts("-----please input-----:");
            scanf("%s", s);
            while(p)
            {
                if(strcmp(p->pro, s) == 0)
                {
                    flag = 1;
                    show(p);
                }
                p = p->next;
            }
            break;
        case'4':
           puts("-----please input-----:");
            scanf("%lf", &cs);
            while(p)
            {
                if(cs == p->pri)
                {
                    flag = 1;
                    show(p);
                }
                p = p->next;
            }
            break;
        case'5':
            char c;
            puts("1-按年查找    2-按具体月份查找     3-按具体日期查找");
            c = getch();
            puts("-----please input-----:");
            switch(c)
            {
            case'1':
                scanf("%d",&ay);
                while(p)
                {
                    if(p->iny == ay)
                    {
                        flag = 1;
                        show(p);
                    }
                    p = p->next;
                }
                break;
            case'2':
                scanf("%d.%d", &ay, &am);
                while(p)
                {
                    if(p->iny == ay &&p->inm == am)
                    {
                        flag = 1;
                        show(p);
                    }
                    p = p->next;
                }
                break;
            case'3':
                scanf("%d.%d.%d", &ay, &am, &ad);
                while(p)
                {
                    if(p->iny == ay && p->inm == am&& p->ind == ad)
                    {
                        flag = 1;
                        show(p);
                    }
                    p = p->next;
                }
                break;
            }
            break;

        case'6':
            char d;
            puts("1-按年查找    2-按具体月份查找     3-按具体日期查找");
            d = getch();
            puts("-----please input-----:");
            switch(d)
            {
            case'1':
                scanf("%d",&ay);
                while(p)
                {
                    if(p->outy == ay)
                    {
                        flag = 1;
                        show(p);
                    }
                    p = p->next;
                }
                break;
            case'2':
                scanf("%d.%d", &ay, &am);
                while(p)
                {
                    if(p->outy == ay &&p->outm == am)
                    {
                        flag = 1;
                        show(p);
                    }
                    p = p->next;
                }
                break;
            case'3':
                scanf("%d.%d.%d", &ay, &am, &ad);
                while(p)
                {
                    if(p->outy == ay && p->outm == am&& p->outd == ad)
                    {
                        flag = 1;
                        show(p);
                    }
                    p = p->next;
                }
                break;
            }
            break;
        }
        if(flag == 0)
            puts("-----查询结果为空!-----");
        return flag;
    }
}
int Modify(ma *head, int *n)
{

    if(*n == 0)
        puts("-----无任何内容，请按'a'添加信息-----");
    else
    {
        int flag = 0;
        puts("-----查找你要修改的信息-----");
        while(flag == 0)
        {
            flag = Find(head, n);
            if(flag == 0)
            {
                puts("是否继续查找\n是.1\n否.2");
                char de;
                de = getch();
                if(de == '2')
                    return 0;
                if(de == '1')
                    puts("-----继续查找-----");
            }
            if(flag == 1)
                break;
        }
        char ser[101], deal[1001];
        double iim;
        int iy, im, id, flags = 1;
        ma *p = head->next;
        while(1)
        {
            puts("-----输入修改单位编号-----");
            scanf("%s", ser);
            p = head->next;
            while(p)
            {
                if(strcmp(p->id, ser) == 0)
                {
                    flags = 1;
                    break;
                }
                else
                {
                    p = p->next;
                    flags = 0;
                }
            }
            if(flags == 1)
                break;
            if(flags == 0)
            {
                puts("输入错误，是否再找？\n1.是\n2.否");
                char i;
                i = getch();
                if(i == '1')
                    continue;
                if(i == '2')
                {
                    puts("修改终止");
                    return 0;
                }
            }
        }
        char dealc;
        puts("1.修改编号\n2.修改名称\n3.修改保管人\n4.修改入库数\n5.修改出库数\n6.修改单价\n7.修改入库时间\n8.修改运动时间\n9.修改备注");
        dealc = getch();

        switch(dealc)
        {
        case'1':
            puts("-----请输入-----");
            scanf("%s", deal);
            strcpy(p->id, deal);
            break;
        case'2':
            puts("-----请输入-----");
            scanf("%s", deal);
            strcpy(p->name, deal);
             break;
        case'3':
            puts("-----请输入-----");
            scanf("%s", deal);
            strcpy(p->pro, deal);
             break;
        case'4':
            puts("-----请输入-----");
            scanf("%lf", &iim);
            p->in = iim;
             break;
        case'5':
            puts("-----请输入-----");
            scanf("%lf", &iim);
            p->out = iim;
        case'6':
            puts("-----请输入-----");
            scanf("%lf", &iim);
            p->pri = iim;
             break;
        case'7':
            puts("-----请输入完整格式的日期-----");
            scanf("%d.%d.%d",&iy, &im, &id);
            p->iny = iy;
            p->inm = im;
            p->ind = id;
            break;
        case'8':
            puts("-----请输入完整格式的日期-----");
            scanf("%d.%d.%d",&iy, &im, &id);
            p->outy = iy;
            p->outm = im;
            p->outd = id;
            break;
        case'9':
            puts("请输入");
            scanf("%s", deal);
            strcmp(p->note, deal);
            break;
        }
        show(p);
    }
    Filew(head);
}
void Add(ma *head, int *n)
{
    ma *p;
    p = head->next;
    while(p)
    {
        if(p->next == NULL)
            break;
        p = p->next;
    }
    puts("输入形式：编号 名称 保管人 入库数 出库数 单价 入库时间 出库时间 备注(不可为空) //时间输入格式：年.月.日 例如 2019.5.31");
    puts("***输入请以编号为“end~”结束***");
    ma *p1, *p2, *head1;
    head1 = (ma *)malloc(sizeof(ma));
    head1->next = NULL;
    int ai = *n;
    char ids[101], names[101], pros[101], notes[10101];
    int inys, inms, inds, flag = 1, flags1 = 1, flags2 = 0;
    int outys, outms, outds;
    double ins, outs, pris;
    while(1)
    {
        while(1)
        {
            scanf("%s", ids);
            if(strcmp(ids,"end~") == 0)
            {
                break;
            }
            scanf("%s %s %lf %lf %lf %d.%d.%d %d.%d.%d %s", names, pros, &ins, &outs, &pris, &inys, &inms, &inds, &outys, &outms, &outds, notes);
            ma *q1 = head->next, *q2 = head1->next;
            while(q1)
            {
                if(strcmp(q1->id, ids) == 0)
                {
                    flags1 = 1;
                    puts("-----输入编号已存在，不可重复，上一条作废-----");
                    break;
                }
                else
                {
                    flags1 = 0;
                    q1 = q1->next;
                }
            }
            while(q2 != NULL && flags1 == 0)
            {
                if(strcmp(q2->id, ids) == 0)
                {
                    flags2 = 1;
                    puts("-----输入编号已存在，不可重复，上一条作废-----");
                    break;
                }
                else
                {
                    flags2 = 0;
                    q2 = q2->next;
                }
            }
            if(flags1 == 0 && flags2 == 0)
                break;
        }
        flags1 = flags2 = 1;
        if(strcmp(ids,"end~") == 0)
        {
                break;
        }
        ai++;
        p1 = (ma *)malloc(sizeof(ma));
        strcpy(p1->id, ids);
        strcpy(p1->name, names);
        strcpy(p1->pro, pros);
        strcpy(p1->note, notes);
        p1->iny = inys;
        p1->inm = inms;
        p1->ind = inds;
        p1->outy = outys;
        p1->outm = outms;
        p1->outd = outds;
        p1->in = ins;
        p1->out = outs;
        p1->pri = pris;
        p1->next = NULL;
        if(head1->next == NULL)
            head1->next = p1;
        else
            p2->next = p1;
        p2 = p1;
    }
    p->next = head1->next;
    *n = ai;
    Filew(head);
}
int Delete(ma *head, int *n)
{
    if(*n == 0)
        puts("无任何内容，请按'a'添加信息");
    else
    {
        int a = *n, f;
        while(1)
        {
            while(1)
            {
                puts("-----查找删除对象-----");
                f = Find(head, n);
                if(f == 0)
                {
                    puts("-----查询为空!-----");
                    puts("-----是否再查?\n1.是\n2.否-----");
                    char i;
                    i = getch();
                    if(i == '1')
                        continue;
                    if(i == '2')
                        return 0;;
                }
                if(f == 1)
                    break;
            }
            ma *p = head;
            int flag = 1;
            char ser[101];
            puts("-----输入删除信息编号-----");
            scanf("%s", ser);
            while(p->next)
            {
                if(strcmp(p->next->id, ser) == 0)
                {
                    p->next = p->next->next;
                    flag = 1;
                    a--;
                    break;
                }
                p = p->next;
                flag = 0;
            }
            if(flag == 0)
                puts("-----输入有误，删除失败-----");
            if(flag == 1)
            {
                Filew(head);
                puts("-----删除成功-----");
            }
            puts("-----是否继续删除-----\n1.是\n2.否");
            char i;
            i = getch();
            if(i == '1')
                continue;
            if(i == '2')
                break;
        }
        *n = a;
    }
}
ma *Filer(int *n)
{
    FILE *fp;
    int a;
    a = *n;
    ma *p1, *p2, *head;
    head = (ma *)malloc(sizeof(ma));
    head->next = NULL;
    char ids[101], names[101], pros[101], notes[10101];
    int inys, inms, inds;
    int outys, outms, outds;
    double ins, outs, pris;
    fp = fopen("data.txt","r");
    for(int i = 1; i <= a; i++)
    {
        p1 = (ma *)malloc(sizeof(ma));
        fscanf(fp, "%s %s %s %lf %lf %lf %d.%d.%d %d.%d.%d %s", ids, names, pros, &ins, &outs, &pris, &inys, &inms, &inds, &outys, &outms, &outds, notes);
        p1 = (ma *)malloc(sizeof(ma));
        strcpy(p1->id, ids);
        strcpy(p1->name, names);
        strcpy(p1->pro, pros);
        strcpy(p1->note, notes);
        p1->iny = inys;
        p1->inm = inms;
        p1->ind = inds;
        p1->outy = outys;
        p1->outm = outms;
        p1->outd = outds;
        p1->in = ins;
        p1->out = outs;
        p1->pri = pris;
        p1->next = NULL;
        if(head->next == NULL)
            head->next = p1;
        else
            p2->next = p1;
        p2 = p1;
    }
    fclose(fp);
    return head;
}
int main()
{
    char i;
    int *n;
    int a;
    n = &a;
    FILE *fpr;
    Filecount();
    fpr = fopen("count.txt", "r");
    fscanf(fpr, "%d", &a);
    ma *head = Filer(n);
    fclose(fpr);
    while(1)
    {
        system("CLS");
        printf("* * * * * *Menue* * * * * *\n");
        printf("*     a. Input   输入     *\n");
        printf("*     b. Display 展示     *\n");
        printf("*     c. Modify  修改     *\n");
        printf("*     d. Find    查找     *\n");
        printf("*     e. Add     添加     *\n");
        printf("*     f. Delete  删除     *\n");
        printf("*     g. Exit    退出     *\n");
        printf("* * * * * * * * * * * * * *\n");
        printf("    Please select a to f    \n");
        i = getch();
        if(i =='g')
        {
            puts("-----感谢您的使用，再见-----");
            break;
        }
        else switch(i)
        {
            case 'a':
                if(*n != 0)
                {
                    puts("数据不为空，若想添加信息请选择Add");
                    puts("若强行写入会造成文件清空，是否进行？\n是--1\n否--2");
                    char esc;
                    esc = getch();
                    if(esc == '2')
                        break;
                    else if(esc == '1')
                        ;
                    else
                        break;
                }
                 head = Createlink(n);
                 puts("**********done**********");
                 printf("目前信息共 %d 条\n", *n);
                 system("pause");
                 break;
            case 'b':
                 Display(head, n);
                 printf("目前信息共 %d 条\n", *n);
                 puts("**********done**********");
                 system("pause");
                 break;
            case 'c':
                 Modify(head, n);
                 puts("**********done**********");
                 system("pause");
                 break;
            case 'd':
                 Find(head, n);
                 puts("**********done**********");
                 system("pause");
                 break;
            case 'e':
                 Add(head, n);
                 puts("**********done**********");
                 printf("目前信息共 %d 条\n", *n);
                 system("pause");
                 break;
            case 'f':
                 Delete(head, n);
                 puts("**********done**********");
                 printf("目前信息共 %d 条\n", *n);
                 system("pause");
                 break;
        }
        fpr = fopen("count.txt", "w");
        fprintf(fpr, "%d", *n);
    }
    fclose(fpr);
}
