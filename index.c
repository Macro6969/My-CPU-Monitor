#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>



struct CPUStats {
    long long user;
    long long nice;
    long long system;
    long long idle;
    long long iowait;
    long long irq;
    long long softirq;
    long long steal;
};



int main()
{
    float previous_idleTime=0.0;
    float previous_totalTime=0.0;
    while (1){


        struct CPUStats stats = {0};
        FILE *ptr;
        ptr = fopen("/proc/stat","r");
        if(ptr == NULL){
            printf("Error opening file\n");
            return 1;
        }
    
        fscanf(ptr, "cpu %lld %lld %lld %lld %lld %lld %lld %lld", &stats.user, &stats.nice, &stats.system, &stats.idle, &stats.iowait, &stats.irq, &stats.softirq, &stats.steal);
        fclose(ptr);
        // printf("\n\nStats After 1Sec\n\n");
        // printf("User: %lld\n", stats.user);
        // printf("Nice: %lld\n", stats.nice);
        // printf("System: %lld\n", stats.system);
        // printf("Idle: %lld\n", stats.idle);
        // printf("IOwait: %lld\n", stats.iowait);
        // printf("IRQ: %lld\n", stats.irq);
        // printf("SoftIRQ: %lld\n", stats.softirq);
        // printf("Steal: %lld\n", stats.steal);
        float current_idleTime= stats.idle + stats.iowait;
        float current_totalTime= stats.idle + stats.iowait +stats.irq+stats.nice+stats.softirq+stats.steal+stats.system+stats.user;
        float delta_idle = (current_idleTime) - (previous_idleTime);
        float delta_total = (current_totalTime) - (previous_totalTime);
        float usage = (1.0 - (delta_idle / delta_total)) * 100.0;
        printf("\rUsage: %6.2f%%", usage);
        
        previous_idleTime=current_idleTime;
        previous_totalTime=current_totalTime;
        if(usage>90.0){

            char command[] = "ps -eo comm,%cpu --sort=-%cpu | head -n 2 | tail -n 1";
            char buffer[128];
    
            // Open a pipe to the command
            FILE* pipe = popen(command, "r");
            if (!pipe) return 1;
    
            // Read the output
            if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
                buffer[strcspn(buffer, "\n")] = '\0';
                printf("\tProcess hoggingg your cpu is: %s", buffer);
                FILE *text;
                text = fopen("./process.txt","a");
                fprintf(text,"Process Hogging Your CPU is: %s\n",buffer);
                fclose(text);
                printf("\033[2J\033[1;1H");
            }
            
            pclose(pipe);
        }
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
