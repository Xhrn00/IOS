//xhryny00
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#define MMAP(pointer) {(pointer) = mmap(NULL, sizeof(*(pointer)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);}
#define UNMAP(pointer) {munmap((pointer), sizeof((pointer)));}


//file proj2.out
FILE *file;


//values for shared memory
int *mail_open = NULL;
int *linenumber = NULL;
int *queue_1 = NULL;
int *queue_2 = NULL;
int *queue_3 = NULL;

void mmmap_init() {
    MMAP(mail_open);
    *mail_open = 1;
    MMAP(linenumber);
    *linenumber = 1;
    MMAP(queue_1)
    *queue_1 = 0;
    MMAP(queue_2)
    *queue_2 = 0;
    MMAP(queue_3)
    *queue_3 = 0;
}

void mmmap_close(){
    UNMAP(mail_open);
    UNMAP(linenumber);
    UNMAP(queue_1);
    UNMAP(queue_2);
    UNMAP(queue_3);
}




//init and destaroy semaphores
sem_t *mutex_mail_c = NULL;
sem_t *mutex_mail_w = NULL;
sem_t *printout = NULL;
sem_t *mutex_delete_client = NULL;
sem_t *mutex_null = NULL;
sem_t *client = NULL;
sem_t *worker = NULL;
sem_t *client_finised = NULL;
sem_t *worker_finised = NULL;
sem_t *queue1 = NULL;
sem_t *queue2 = NULL;
sem_t *queue3 = NULL;



int sems_close(){
    if (sem_destroy(mutex_mail_c) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(mutex_mail_c);

    if (sem_destroy(mutex_mail_w) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(mutex_mail_w);

    if (sem_destroy(printout) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(printout);

    if (sem_destroy(mutex_delete_client) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(mutex_delete_client);

    if (sem_destroy(mutex_null) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(mutex_null);

    
    
    if (sem_destroy(client) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(client);
    
    if (sem_destroy(worker) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(worker);

    if (sem_destroy(client_finised) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(client_finised);

    if (sem_destroy(worker_finised) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(worker_finised);

    if (sem_destroy(queue1) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(queue1);

    if (sem_destroy(queue2) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(queue2);

    if (sem_destroy(queue3) == -1) {
        fprintf(stderr,"sem_destroy");
    }
    UNMAP(queue3);

    return 0;
}




int sems_init(){
    MMAP(mutex_mail_c);
    if (sem_init(mutex_mail_c, 1, 1) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(mutex_mail_w);
    if (sem_init(mutex_mail_w, 1, 1) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }


    MMAP(printout);
    if (sem_init(printout, 1, 1) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(mutex_delete_client);
    if (sem_init(mutex_delete_client, 1, 1) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(mutex_null);
    if (sem_init(mutex_null, 1, 1) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(client);
    if (sem_init(client, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(worker);
    if (sem_init(worker, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(client_finised);
    if (sem_init(client_finised, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(worker_finised);
    if (sem_init(worker_finised, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(queue1);
    if (sem_init(queue1, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(queue2);
    if (sem_init(queue2, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    MMAP(queue3);
    if (sem_init(queue3, 1, 0) == -1) {
        sems_close();
        mmmap_close();
        fclose(file);
        fprintf(stderr,"sem_init");
        return 1;
    }

    return 0;
}





//queue functions

void add_to_queue(int type_of_service) {
   if (type_of_service == 1)
   {
    (*queue_1)++;
    sem_wait(queue1);
   }
   if (type_of_service == 2)
   {
    (*queue_2)++;
    sem_wait(queue2);
   }
   if (type_of_service == 3)
   {
    (*queue_3)++;
    sem_wait(queue3);
   }
}


int choose_queue(int queue){
    srand(time(NULL));
    int queue_arr[3] = {*queue_1, *queue_2, *queue_3};
    int count_of_queue[3] = {0};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (queue_arr[i] > 0)
        {
            count_of_queue[j] = i + 1;
        }
        }
    }
    
    int all_zeros = 1;
    for (int i = 0; i < 3; i++) 
    {
        if (count_of_queue[i] != 0) 
        {
        all_zeros = 0;
        break;
        }
    }
    if (all_zeros == 1)
    {
        return queue;
    }
    
    while (1)
    {
        int new_queue = rand() % 3;
        if (count_of_queue[new_queue] != 0)
        {
            queue = count_of_queue[new_queue];
            break;
        }
    }
    
    if (queue == 1)
    {
        sem_post(queue1);
    }
     if (queue == 2)
    {
        sem_post(queue2);
    }
     if (queue == 3)
    {
        sem_post(queue3);
        
    }
    return queue;
}


void delete_client(int queue){
    if (queue == 1)
    {
        (*queue_1)--;
    }
     if (queue == 2)
    {
        (*queue_2)--;
    }
     if (queue == 3)
    {
        (*queue_3)--;
    }
}



//client process

void client_process(int idZ, int TZ){

    sem_wait(printout);
    fprintf(file,"%d: Z %d: started\n", (*linenumber)++,idZ);
    fflush(file);
    sem_post(printout);
    
    srand(time(NULL) + idZ);
    int sleep_time = rand() % (TZ + 1);
    usleep(sleep_time * 1000);
    
    sem_wait(mutex_mail_c);
    sem_wait(mutex_null);
    if ((*mail_open) == 0)
    {
        sem_wait(printout);
        fprintf(file,"%d: Z %d: going home\n",(*linenumber)++,idZ);
        fflush(file);
        sem_post(printout);
        sem_post(mutex_mail_c);
        sem_post(mutex_null);
        exit(0);
    }else
    {
        int X = rand() % 3 + 1;
        sem_wait(printout);
        fprintf(file,"%d: Z %d: entering office for a service %d\n", (*linenumber)++, idZ, X);
        fflush(file);
        sem_post(printout);
        sem_post(mutex_mail_c);
        sem_post(mutex_null);
        
        add_to_queue(X);
        
        sem_wait(worker);
        sem_wait(printout);
        fprintf(file,"%d: Z %d: called by office worker\n",(*linenumber)++, idZ);
        fflush(file);
        sem_post(printout);
        sem_post(client);

        sleep_time = rand() % 10;
        usleep(sleep_time * 1000);
        sem_wait(worker_finised);

        sem_wait(printout);
        fprintf(file,"%d: Z %d: going home\n",(*linenumber)++,idZ);
        fflush(file);
        sem_post(printout);
        sem_post(client_finised);
        exit(0);
    }
}

//worker process

void worker_process(int idU, int TU){
    
    sem_wait(printout);
    fprintf(file,"%d: U %d: started\n", (*linenumber)++,idU);
    fflush(file);
    sem_post(printout);
    
    while (1)
    {
    int q = 0;
        sem_wait(mutex_mail_w);
        if ((*mail_open) == 0 && ((*queue_1) == 0 && (*queue_2) == 0 && (*queue_3) == 0))
        {
                sem_wait(printout);
                fprintf(file,"%d: U %d: going home\n", (*linenumber)++,idU);
                fflush(file);
                sem_post(printout);
                sem_post(mutex_mail_w);
                exit(0);
        }
        
         if ((*mail_open) == 1 && ((*queue_1) == 0 && (*queue_2) == 0 && (*queue_3) == 0))
        {
            sem_wait(printout);
            fprintf(file,"%d: U %d: taking break\n", (*linenumber)++,idU);
            fflush(file);
            sem_post(printout);

            srand(time(NULL) + idU);
            int sleep_time = rand() % (TU + 1);
            usleep(sleep_time * 1000);

            sem_wait(printout);
            fprintf(file,"%d: U %d: break finished\n", (*linenumber)++,idU);
            fflush(file);
            sem_post(printout);
        }else
        {
            while (q == 0)
            {
                q = choose_queue(q);
            }
          
            sem_post(worker);
            sem_wait(client);
            sem_wait(printout);
            fprintf(file,"%d: U %d: serving a service of type %d\n", (*linenumber)++, idU, q);
            fflush(file);
            sem_post(printout);
            
            srand(time(NULL));
            int sleep_time = rand() % 10;
            usleep(sleep_time * 1000);
            sem_post(worker_finised);

            sem_wait(printout);
            fprintf(file,"%d: U %d: service finished\n", (*linenumber)++,idU);
            fflush(file);
            sem_post(printout);
            sem_wait(mutex_delete_client);

            delete_client(q);
            sem_post(mutex_delete_client);
            sem_wait(client_finised);
        }
        sem_post(mutex_mail_w);
    }
    exit(0);
}



int main(int argc, char *argv[]){
 // Checking inputs 
    if (argc != 6)
    {
        fprintf(stderr,"Incorrect numbers of input!\n");               
        return 1;
    }

    int argv_int[100];
    int num_count = 0;

    for (int i = 1; i < 6; i++)          
    {
        char *endptr;
        long val = strtol(argv[i], &endptr, 10);              
        if (errno == ERANGE || *endptr != '\0') {
            fprintf(stderr, "Invalid input: %s\n", argv[i]);
            return 1;
        }
        if (val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Value out of range: %s\n", argv[i]);
            return 1;
        }

        argv_int[num_count] = (int) val;
        num_count++;
    }

    if (argv_int[1] == 0 || argv_int[2] < 0 ||argv_int[2] > 10000 ||argv_int[3] < 0 ||argv_int[3] > 100 || argv_int[4] < 0 ||argv_int[4] > 10000)
    {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }
    
//Inicialization values for processes
    int NZ = argv_int[0];
    int NU = argv_int[1];
    int TZ = argv_int[2];
    int TU = argv_int[3];
    int F = argv_int[4];
  
 //main process 
    int status = 0;
    file = fopen("proj2.out", "w");
    if (file == NULL) {
    fprintf(stderr,"Error opening file.\n");
    return 1;
    }

    mmmap_init();
    sems_init();
    pid_t waits;
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr,"fork\n");
        return 1;
    } 
    else if (pid == 0) {
    
        
// Inicialization of client process        
    for (int i = 0; i < NZ; i++){
        pid_t pid = fork();
        if (pid == -1) {
            sems_close();
            mmmap_close();
            fclose(file);
            fprintf(stderr,"fork\n");
            return 1;
        } else if (pid == 0) {
            client_process(i+1,TZ);
            exit(0);
        }
        }
// Inicialization of worker process 
    for (int i = 0; i < NU; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            sems_close();
            mmmap_close();
            fclose(file);
            fprintf(stderr,"fork\n"); 
            return 1;
        } else if (pid == 0) {
            worker_process(i+1,TU);
            exit(0);
        }
    }

        srand(time(NULL));
        int sleep_time;
        if (F == 0) {
            sleep_time = 0;
        } else if (F == 1) {
            sleep_time = 1;
        }
         else {
         sleep_time = F / 2 + rand() % (F / 2);
        }
        usleep(sleep_time * 1000);

        sem_wait(mutex_null);
        *mail_open = 0;
        sem_wait(printout);
        fprintf(file,"%d: closing\n", (*linenumber)++);
        fflush(file);
        sem_post(printout);
        sem_post(mutex_null);
    } 
    while ((waits = wait(&status)) > 0);
    sems_close();
    mmmap_close();
    fclose(file);
    exit(0);
    return 0;
}