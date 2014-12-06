#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace std;

//----------------------------------------------------
/* Initialization */
//----------------------------------------------------

string filename[4]={"testdata1.txt", 
                    "testdata2.txt", 
                    "testdata3.txt", 
                    "testdata4.txt"};

string RESULT_FILE = "Result.txt";


int const thread_count = 5;                            /* 4 read 1 writes */

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;        /* Initialize mutex lock */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;        /* Initialize pthread condition */

unsigned event_flags = 0;
unsigned finished_flags = 0;                           /* Check whether read thread finished */

ofstream resultfile;                                   /* Declare result file */

pthread_key_t key;                                     /* Thread local Storage Key */

int global_sum = 0;                                    /* Share Memory */
int write_sum = 0;

//----------------------------------------------------
/* Function Protocol */
//----------------------------------------------------

void *read(void*);
void *write(void*);

//----------------------------------------------------
/* Main function */
//----------------------------------------------------

int main(int argc, const char *argv[])
{
    /* Prepare for pthread_create */
    pthread_t *threads = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_key_create(&key, NULL);

    /* open result file */
    resultfile.open(RESULT_FILE);

    /* use long in case of a 64-bit system */
    long thread;
    for(thread = 0; thread < thread_count; thread++) {
        if(thread < thread_count - 1)
            pthread_create(&threads[thread], &attr, read, (void*) thread);
        else
            pthread_create(&threads[thread], &attr, write, (void*) thread);
    }

    for (thread= 0; thread < thread_count; thread++) {
        pthread_join(threads[thread], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mu);
    free(threads);
    return 0;
}

/* Implementation */

void *read(void* thread_id)
{
    long tid = (long)thread_id;
    int flag = 1 << tid;
    string line;

    /* Thread Local Storage: sum */
    int *sum = (int *)malloc(sizeof(int));
    *sum = 0;
    pthread_setspecific(key, sum);

    ifstream testfile(filename[tid]);

    if (testfile.is_open()) 
    {
        while(getline(testfile, line)) 
        {
            *sum += atoi(line.c_str());

            /* if line equals wait */
            if(line.compare("wait") == 0) {

                /* after wait, set sum to 0 */
                *sum = 0;
            }
        }
    }
    else {
        cout << "Unable to open file, check out the name of file.\n";
    }
    pthread_setspecific(key, NULL);
    free(sum);
    testfile.close();

    return NULL;
}

void *write(void* thread_id) 
{
    long   tid = (long)thread_id;
    int    count = 1;    /* Count the number of Global Sum */

    
    

    return NULL;
}
