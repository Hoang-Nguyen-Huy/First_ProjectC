#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <commdlg.h>
#define FP(i, a, b) for (ll i = a; i <= b; i++)
#define FPT(i, a, b) for (ll i = a; i >= b; i--)
#define ll long long
#define f first
#define s second
ll exitt, qr, accnum, listnum, songnum, quaw[500][500], pause = 0, numnhac, queuenum, queueid[500];
typedef struct
{
    ll first;
    char second[500];
    ll id;
} Pair;
Pair song_au[500];
int compare_pairs(const void *a, const void *b)
{
    const Pair *p1 = (const Pair *)a;
    const Pair *p2 = (const Pair *)b;
    return (p1->first - p2->first);
}
struct acc
{
    char use[500];
    char pass[500];
} list_acc[500];
struct list
{
    char name_list[500];
    ll id;
    ll sl;
    char name_song[500];
    char au[500];
    char namenhac[500];
} list_play[500], list_songplay[500][500], list_song[500], listnhac[500];
FILE *f;
FILE *fcheck;
void playsong(ll id, ll todo)
{
    // system("cls");
    // phat nhac theo id tu search song
     char nhac0[500];
    if (todo == 1)
    {
        f = fopen("queue.txt","w");
      //  printf("%lli\n",id);
        fprintf(f,"%lli\n%lli",1,id);
        fclose(f);
        FP(i, 0, strlen(listnhac[id].namenhac))
        {
            nhac0[i] = listnhac[id].namenhac[i];
        }
            PlaySound(nhac0, NULL, SND_ASYNC);
       pause = 1;
    }
    // phat nhac trong queue
    if (todo == 2)
    {
       
        FP(i, 0, strlen(listnhac[id].namenhac))
        {
            nhac0[i] = listnhac[id].namenhac[i];
        }
        if (pause == 0)
        {
            PlaySound(nhac0, NULL, SND_ASYNC);
        }
        else
        {
            PlaySound(NULL, NULL, SND_PURGE);
        }
        pause = 1 - pause;
    }
}
void delete_new_line(char x[])
{
    ll len = strlen(x);
    if (x[len - 1] == '\n')
    {
        x[len - 1] = '\0';
    }
}
void rewrite(ll zan, ll n)
{
    if (zan == 1)
    {
        f = fopen("playlist.txt", "w");
        fprintf(f, "%lli\n", listnum);
        FP(i, 1, listnum)
        {
            fprintf(f, "%s\n", list_play[i].name_list);
            fprintf(f, "%lli\n", list_play[i].id);
            fprintf(f, "%lli\n", list_play[i].sl);
            FP(j, 1, list_play[i].sl)
            {
                fprintf(f, "%lli\n", quaw[i][j]);
            }
        }
        fclose(f);
    }
}
ll max(ll a, ll b)
{
    return (a > b) ? a : b;
}
ll kh(char tx1[500], char tx2[500])
{
    ll n = max(strlen(tx1), strlen(tx2)), dem1 = 0;
    FP(i, 0, n - 1)
    {
        if (tx1[i] == tx2[i])
        {
            dem1++;
        }
    }
    return dem1;
}
void add_play(ll id)
{
}
ll check_add(ll id, ll vt)
{
    FP(j, 1, list_play[id].sl)
    {
        if (quaw[id][j] == vt)
            return 0;
    }
    return 1;
}
void add_song(ll id, ll vt, ll todo)
{
    ll check0 = 1;
    char song0[500], au0[500];
    system("cls");
    if (check_add(id, vt) == 0)
    {
        printf("\nThis song already exists in this playlist !\n\n");
        printf("PRESS ANY KEY TO CONTINUE...");
        getch();
    }
    else
    {
        if (todo == 1)
        {

            list_play[id].sl++;
            ll j = list_play[id].sl;
            quaw[id][j] = vt;
            printf("\n SUCCESSFLLY! \n\n");
            printf("PRESS ANY KEY TO CONTINUE...");
            getch();
            rewrite(1, listnum);
        }
        if (todo == 2)
        {

            list_play[id].sl++;
            ll j = list_play[id].sl;
            quaw[id][j] = vt;
            printf("\n SUCCESSFLLY! \n");
            rewrite(1, listnum);
        }
    }
}
void remove_song(ll id)
{
    ll bz;
    system("cls");
    printf("----- WHICH SONG DO  YOU WANT TO REMOVE -----\n");
    FP(i, 1, list_play[id].sl)
    {
        ll id0 = quaw[id][i];
        printf("%lli.%s (%s)\n", i, list_song[id0].name_song, list_song[id0].au);
    }
    printf("Enter your choice: ");
    scanf("%lli", &bz);

    FP(i, bz, list_play[id].sl)
    {
        quaw[id][i] = quaw[id][i + 1];
    }
    list_play[id].sl--;
    rewrite(1, listnum);
    printf("\n SUCCESSFLLY!\n\n");
    printf(" PRESS ANY KEY TO CONTINUE...\n");
    getch();
}
void de_playlist(ll id)
{
    // memset(list_play[id].name_list, 0, sizeof(list_play[id].name_list));
    FP(i, 1, list_play[id].sl)
    {
        // printf("%lli\n",quaw[id][i]);
        quaw[id][i] = 0;
    }
    list_play[id].id = 0;
    list_play[id].sl = 0;
    FP(i, id, listnum - 1)
    {
        // printf("1");
        list_play[i].id = list_play[i + 1].id;
        list_play[i].sl = list_play[i + 1].sl;
        FP(j, 0, strlen(list_play[i + 1].name_list) - 1)
        {
            // printf("%lli\n",j);
            list_play[i].name_list[j] = list_play[i + 1].name_list[j];
        }
        FP(j, 1, list_play[i].sl)
        {
            quaw[i][j] = quaw[i + 1][j];
        }
    }
    listnum--;
    system("cls");
    printf("\n\nSUCCESSFULLY !\n\n");
    printf("PRESS ANY KEY TO CONTINUE...");
    getch();
    /*  printf("%lli\n",listnum);
         FP(i, 1, listnum)
        {
            printf("%s\n%lli\n%lli\n",list_play[i].name_list,list_play[i].id,list_play[i].sl);
            FP(j,1,list_play[i].sl)
            {
              printf("%lli\n",quaw[i][j]);
            }
        }
        getch();*/
    rewrite(1, listnum);
}
ll check_log()
{
    char username[50], pass[50];
    system("cls");
    printf("Enter your username : ");
    scanf("%s", &username);
    printf("Enter your password : ");
    scanf("%s", &pass);
    ll n = 0;
    fcheck = fopen("acc.txt", "r");
    fscanf(fcheck, "%lli", &n);
    // printf("%s\n %s",username,pass);
    // printf("%lli \n",n);
    // printf("%lli\n",strcmp(s2,username));
    ll m = n;
    FP(i, 1, m)
    {
        char u[50], v[50];
        fscanf(fcheck, "%s %s", &u, &v);
        // printf("%lli %lli  ",i,n);
        // printf("%s%lli \n",u,1);
        // getch();
        // return 1;
        // printf("%lli \n",strcmp(u,username));
        if (strcmp(u, username) == 0 && strcmp(v, pass) == 0)
        {
            fclose(fcheck);
            return 1;
        }
        if (strcmp(u, username) == 0 && strcmp(v, pass) != 0)
        {
            fclose(fcheck);
            return 0;
        }
    }
    fclose(fcheck);
    return 0;
}
void playlist1(ll vt, ll todo)
{
    ll cap = 1;
    while (cap == 1)
    {
        ll bz = 1;
        system("cls");
        printf("----- YOUR PLAYLISTS -----\n\n");
        FP(i, 1, listnum)
        {
            printf("%lli.Name playlist: %s\n", i, list_play[i].name_list);
        }
        printf("0.back");
        printf("\nEnter your number: ");
        scanf("%lli", &bz);
        if (bz == 0)
            cap = 0;
        else
        {
            if (todo == 2)
            {
                add_song(bz, vt, 1);
                cap = 0;
            }
        }
    }
}
void add_song_playlist(ll id)
{
    system("cls");
    playlist1(id, 2);
}
void search_song(ll id, ll todo)
{
    memset(song_au, 0, sizeof(song_au));
    system("cls");
    fflush(stdin);
    char song0[500];
    ll dem = 0, choice = 0, choice1 = 0;
    printf("Enter name song: ");
    fgets(song0, 100, stdin);
    delete_new_line(song0);
    FP(i, 1, songnum)
    {
        ll bbi = kh(list_song[i].name_song, song0);
        ll id0 = i;
        if (bbi > 0)
        {
            dem++;
            song_au[dem].first = bbi;
            FP(j, 0, strlen(list_song[i].name_song) - 1)
            {
                song_au[dem].second[j] = list_song[i].name_song[j];
            }
            song_au[dem].id = i;
        }
    }
    system("cls");
    qsort(song_au, dem, sizeof(Pair), compare_pairs);
    if (dem > 0)
    {
        FPT(i, dem, 1)
        {
            printf("%lli.%s\n", dem - i + 1, song_au[i].second);
        }
        printf("0. Back to menu\n");
        printf("Choice your song : ");
        scanf("%lli", &choice);
        if (choice != 0)
        {
            choice = dem - choice + 1;
            ll choice0 = song_au[choice].id;
            if (todo == 1)
            {
                system("cls");
                printf("1. play now\n");
                printf("2. add to queue\n");
                printf("3. add to playlist\n");
                printf("4. back to menu \n");
                printf("0. exit\n");
                printf("Enter your choice : ");
                scanf("%lli", &choice1);
                switch (choice1)
                {
                case 1:
                    playsong(choice0,1);
                    break;
                case 2:
                    add_play(choice0);
                    break;
                case 3:
                    add_song_playlist(choice0);
                    break;
                case 4:
                    break;
                case 0:
                    system("cls");
                    printf("SEE YOU SOON! \n\n");
                    exit(0);
                    break;
                default:
                    break;
                }
            }
            if (todo == 2)
            {
                add_song(id, choice0, 1);
            }
        }
    }
    else
    {
        printf("NO RESULT!\n\n");
        if (todo == 2)
            printf("PRESS ANY KEY TO CONTINUE...");
        getch();
    }
}
void add_playlist()
{
    char namelis[500];
    system("cls");
    ll bz = 1, bzan = 0;
    while (bz)
    {
        bz = 0;
        printf("Enter name list: ");
        fflush(stdin);
        fgets(namelis, 100, stdin);
        delete_new_line(namelis);
        FP(i, 1, listnum)
        {
            if (strcmp(list_play[i].name_list, namelis) == 0)
            {
                printf("\n THE NAME LIST IS ALREADY TAKEN ! \n\n");
                printf(" PRESS ANY KEY TO TRY AGAIN...\n");
                getch();
                system("cls");
                bz = 1;
                break;
            }
        }
    }
    listnum++;
    list_play[listnum].sl = 0;
    list_play[listnum].id = listnum;
    FP(i, 0, strlen(namelis) - 1)
    {
        list_play[listnum].name_list[i] = namelis[i];
    }
    printf("\n SUCCESSFULLY!  \n\n");
    printf(" PRESS ANY KEY TO CONTINUE...\n");
    getch();
    system("cls");
    printf(" ----- PLAYLIST %s -----\n", namelis);
    printf("1.Add song\n");
    printf("2.Back\n");
    printf("Enter your choice: ");
    scanf("%lli", &bzan);
    if (bzan == 2)
    {
        printf("\n PRESS ANY KEY TO CONTINUE...\n");
    }
    if (bzan == 1)
    {
        search_song(listnum, 2);
    }
    else
        rewrite(1, listnum);
}
void cass4(ll qr)
{
     ll choice0 = 0, dem = 0,ax[500];
        memset(ax,0,sizeof(ax));
            system("cls");
            FP(i, 1, list_play[qr].sl)
            {
                 ll id0 = quaw[qr][i];
            dem++;
            ax[dem] = id0;
            // printf("%lli\n",id0);
            printf("%lli.%s (%s)  \n",i, list_song[id0].name_song, list_song[id0].au);
            }
            printf("Enter your song number: ");
            scanf("%lli",&choice0);
            playsong(ax[choice0],1);
}
void showlist(ll qr)
{
    ll bb = 1;
    while (bb)
    {
        ll bzan;
        system("cls");
        printf(" ----- PLAYLIST %s -----\n", list_play[qr].name_list);
        // printf("%lli\n",qr);
        FP(i, 1, list_play[qr].sl)
        {
            ll id0 = quaw[qr][i];
            printf(" %s (%s)  \n", list_song[id0].name_song, list_song[id0].au);
        }
        printf("1.Add song\n");
        printf("2.Remove song\n");
        printf("3.delete playlist\n");
        printf("4.Play music\n");
        printf("0.Back\n");
        printf("5.Exit\n");
        printf("Enter your choice: ");
        scanf("%lli", &bzan);
        switch (bzan)
        {
        case 1:
            search_song(qr, 2);
            break;
        case 2:
            remove_song(qr);
            break;
        case 3:
            bb = 0;
            de_playlist(qr);
            break;
        case 4:
           cass4(qr);
            break;
        case 0:
            bb = 0;
            break;
        case 5:
            system("cls");
            printf("SEE YOU SOON!\n");
            exit(0);
            break;
        default:

            break;
        }
    }
}
void playlist(ll vt, ll todo)
{
    ll cap = 1;
    while (cap == 1)
    {
        ll bz = 1;
        system("cls");
        printf("----- YOUR PLAYLISTS -----\n");
        FP(i, 1, listnum)
        {
            printf("%lli.Name playlist: %s\n", i, list_play[i].name_list);
        }
        printf("0.back");
        printf("\nEnter your number: ");
        scanf("%lli", &bz);
        if (bz == 0)
            cap = 0;
        else
        {
            if (todo == 1)
                showlist(bz);
            if (todo == 2)
            {
                add_song(bz, vt, 2);
                cap = 0;
            }
        }
    }
}
void music_input()
{
    f = fopen("queue.txt", "r");
    fscanf(f, "%lli\n", &queuenum);
    FP(i, 1, queuenum)
    {
        fscanf(f, "%lli\n", &queueid[i]);
    }
    fclose(f);
    f = fopen("filenhac.txt", "r");
    fscanf(f, "%lli\n", &numnhac);
    // printf("%lli\n",numnhac);
    FP(i, 1, numnhac)
    {
        fscanf(f, "%s\n", &listnhac[i].namenhac);
        //  printf("%s\n",listnhac[i].namenhac);
    }
    // getch();
    fclose(f);
    f = fopen("songlist.txt", "r");
    fscanf(f, "%lli\n", &songnum);
    FP(i, 1, songnum)
    {
        fscanf(f, "%lli\n", &list_song[i].id);
        fgets(list_song[i].name_song, sizeof(list_song[i].name_song), f);
        delete_new_line(list_song[i].name_song);
        fgets(list_song[i].au, sizeof(list_song[i].au), f);
        delete_new_line(list_song[i].au);
    }
    printf("%lli\n", songnum);
    /*  FP(i, 1, songnum)
      {
          printf("%lli %s %s\n",list_song[i].id,list_song[i].name_song,list_song[i].au);
      }
      getch();*/
    fclose(f);
    f = fopen("acc.txt", "r");
    fscanf(f, "%lli\n", &accnum);
    FP(i, 1, accnum)
    {
        fscanf(f, "%s %s\n", list_acc[i].use, list_acc[i].pass);
        // printf("%s %s\n",list_acc[i].use,list_acc[i].pass);
    }
    // getch();
    fclose(f);
    f = fopen("playlist.txt", "r");
    fscanf(f, "%lli\n", &listnum);
    printf("%lli\n", listnum);
    FP(i, 1, listnum)
    {
        fflush(stdin);
        fgets(list_play[i].name_list, sizeof(list_play[i].name_list), f);
        delete_new_line(list_play[i].name_list);
        fscanf(f, "%lli\n", &list_play[i].id);
        fscanf(f, "%lli\n", &list_play[i].sl);
        // printf("%s\n%lli\n%lli\n", list_play[i].name_list, list_play[i].id, list_play[i].sl);
        FP(j, 1, list_play[i].sl)
        {
            fscanf(f, "%lli\n", &quaw[i][j]);
            // printf("%lli\n", quaw[i][j]);
        }
    }
    // getch();
    fclose(f);
}
void Menu(ll tt)
{
    if (tt == 1)
    {
        ll ch = 1;
        while (ch)
        {
            if (check_log())
            {
                tt = 2;
                ch = 0;
            }
            else
            {
                system("cls");
                printf("YOUR LOGIN CREDENTAILS DON'T MATCH ON ACCOUNT IN OUR SYSTEM! \n\n");
                printf("1.Try again \n");
                printf("0.Back \n");
                printf("Enter your choice: ");
                scanf("%lli", &qr);
                if (qr == 0)
                {
                    ch = 0;
                }
            }
        }
    }
    if (tt == 2)
    {
        ll ex = 1;
        while (ex)
        {
            music_input();
            system("cls");
            printf("----- WELCOME TO MELODIA -----\n");
            printf("1.Search song\n");
            printf("2.Add playlist\n");
          //  printf("3.Play Music\n");
            printf("3.Your playlist\n");
            printf("4.Play/pause music\n");
            printf("5.Log out\n");
            printf("0.Exit\n\n");
            printf("Enter your choice: ");
            scanf("%lli", &qr);
            switch (qr)
            {
            case 0:
                system("cls");
                printf("SEE YOU SOON! \n\n");
                exitt = 1;
                exit(0);

            case 1:

                system("cls");
                search_song(1, 1);
                // printf("\n PRESS ANY KEY TO CONTINUE...\n");
                break;
            case 2:
                system("cls");
                add_playlist();
                break;
          /*  case 3:
                system("cls");
                play_music(1, 0);
                //  printf("\n PRESS ANY KEY TO CONTINUE...\n");
                break;*/
            case 3:
                system("cls");
                playlist(0, 1);
                //  printf("\n PRESS ANY KEY TO CONTINUE...\n");
                break;
            case 4:
                playsong(queueid[1],2);
                break;
            case 5:
                ex = 0;
                // printf("\n PRESS ANY KEY TO CONTINUE...\n");
                break;
            default:
                printf("PLEASE PRESS A NUMBER...\n");
            }
            printf("\n PRESS ANY KEY TO CONTINUE...\n");
            getch();
        }
    }
}
void addacc(char use[500], char pas[500])
{
    f = fopen("acc.txt", "w");
    accnum++;
    FP(i, 0, strlen(use) - 1)
    {
        list_acc[accnum].use[i] = use[i];
    }
    FP(i, 0, strlen(pas) - 1)
    {
        list_acc[accnum].pass[i] = pas[i];
    }
    fprintf(f, "%lli\n", accnum);
    FP(i, 1, accnum)
    {
        fprintf(f, "%s %s\n", list_acc[i].use, list_acc[i].pass);
    }
    fclose(f);
}
void sign_up()
{
    char username[50], pass[50], pass2[50];
    ll kk = 1, bz = 1;
    system("cls");
    while (bz)
    {
        bz = 0;
        printf("Enter your username : ");
        scanf("%s", &username);
        FP(i, 1, accnum)
        {
            if (strcmp(list_acc[i].use, username) == 0)
            {
                printf("\n YOUR USERNAME IS ALREADY TAKEN ! \n\n");
                printf(" PRESS ANY KEY TO TRY AGAIN...\n");
                getch();
                system("cls");
                bz = 1;
                break;
            }
        }
    }
    while (kk)
    {
        system("cls");
        printf("Enter your username : %s\n", username);
        printf("Enter your password : ");
        scanf("%s", &pass);
        printf("Enter your password again : ");
        scanf("%s", &pass2);
        if (strcmp(pass, pass2) == 0)
        {
            kk = 0;
            addacc(username, pass);
            printf("\n SUCESSFULLY! \n\n");
            printf(" PRESS ANY KEY TO CONTINUE...\n");
            getch();
            Menu(2);
        }
        else
        {
            printf("\n PASSWORD INCORRECT !\n\n");
            printf("PRESS ANY KEY TO TRY AGAIN...\n");
            getch();
        }
    }
}
void login()
{
    music_input();
    while (1)
    {
        system("cls");
        if (exitt)
            exit(0);
        printf("----- WELCOME TO MELODIA -----\n");
        printf("1.Sign in\n");
        printf("2.sign up\n");
        printf("0.Exit\n");
        printf("Enter your choice: ");
        scanf("%lli", &qr);
        switch (qr)
        {
        case 0:
            system("cls");
            printf("SEE YOU SOON! \n\n");
            exit(0);
        case 1:
            Menu(1);
            break;
        case 2:
            sign_up();
            break;
        default:
            printf("PLEASE PRESS A NUMBER...\n");
        }
    }
}
int main()
{
    login();
}