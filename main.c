///* DriverLib Includes */
//#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//
///* Standard Includes */
//#include <stdint.h>
//#include <stdbool.h>
//
//
//#include <stdio.h>
//
//uint8_t base;
//
//struct ImagePair {
//    uint8_t * word;
//    uint8_t * fileType;
//    uint8_t fileSize;
//    unsigned char * image;
//};
//
//uint8_t var;
//
//bool wordFlag = false;
//bool imageFlag = false;
//
//const eUSCI_UART_ConfigV1 uartConfig =
//{
//        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
//        78,                                     // BRDIV = 78
//        2,                                       // UCxBRF = 2
//        0,                                       // UCxBRS = 0
//        EUSCI_A_UART_NO_PARITY,                  // No Parity
//        EUSCI_A_UART_LSB_FIRST,                  // LSB First
//        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
//        EUSCI_A_UART_MODE,                       // UART mode
//        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
//};
////![Simple UART Config]
//
//int main(void)
//{
//    /* Halting WDT  */
//    MAP_WDT_A_holdTimer();
//
//    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
//
//    /* Selecting P1.2 and P1.3 in UART mode */
//    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
//            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
//
//    /* Setting DCO to 12MHz */
//    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
//
//    //![Simple UART Example]
//    /* Configuring UART Module */
//    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
//
//    /* Enable UART module */
//    MAP_UART_enableModule(EUSCI_A0_BASE);
//
//    /* Enabling interrupts */
//    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
//    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
//    MAP_Interrupt_enableSleepOnIsrExit();
//    MAP_Interrupt_enableMaster();
//    //![Simple UART Example]
//
//    while(1)
//    {
//        MAP_PCM_gotoLPM0();
//
//
//    }
//}
//
///* EUSCI A0 UART ISR - Echoes data back to PC host */
//void EUSCIA0_IRQHandler(void)
//{
//    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
//
//    //MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);
//
//    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
//    {
//        var = MAP_UART_receiveData(EUSCI_A0_BASE);
//        MAP_UART_transmitData(EUSCI_A0_BASE, MAP_UART_receiveData(EUSCI_A0_BASE));
//        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
//    }
//
//    //GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
//    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
//}






//#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include <string.h>
//
//#define BUFFER_SIZE 8000
//
//uint8_t base;
//
//typedef struct{
//    uint8_t data[BUFFER_SIZE];
//    uint8_t head;
//    uint8_t tail;
//    uint8_t isFullFlag;
//} CircularBuffer;
//
//int bufferIsFull(CircularBuffer * buffer){
//    return buffer->isFullFlag;
//}
//
//int bufferIsEmpty(CircularBuffer * buffer){
//    int temp = 0;
//    if((buffer->head == buffer->tail) && (buffer->isFullFlag != 1)){
//        temp = 1;
//    }
//    return temp;
//}
//
//void writeToBuffer(CircularBuffer * buffer, uint8_t data_element){
//    if(bufferIsFull(buffer)){
//        //do nothing
//    }else{
//        buffer->data[buffer->head] = data_element;
//        buffer->head = (buffer->head + 1) % BUFFER_SIZE;
//        if(buffer->head == buffer->tail){
//            buffer->isFullFlag = 1;
//        }
//    }
//}
//
//void readFromBuffer(CircularBuffer * buffer){
//    if(bufferIsEmpty(buffer)){
//        //do nothing
//    }else{
//        buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
//        buffer->isFullFlag = 0;
//    }
//}
//
//CircularBuffer * newCircularBuffer(CircularBuffer * buffer){
//    buffer->head = 0;
//    buffer->tail = 0;
//    buffer->isFullFlag = 0;
//    return buffer;
//}
//
//const eUSCI_UART_ConfigV1 uartConfig =
//{
//        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
//        78,                                     // BRDIV = 78
//        2,                                       // UCxBRF = 2
//        0,                                       // UCxBRS = 0
//        EUSCI_A_UART_NO_PARITY,                  // No Parity
//        EUSCI_A_UART_LSB_FIRST,                  // LSB First
//        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
//        EUSCI_A_UART_MODE,                       // UART mode
//        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
//};
//
//CircularBuffer * importedData;
//
////-----------testing-------------
////uint8_t bufferWatch = importedData->data;
////uint8_t var[8000];
////-------------------------------
//
//int main(void)
//{
//    /*Halt Watchdog Timer*/
//    MAP_WDT_A_holdTimer();
//
//    /* Selecting P1.2 and P1.3 in UART mode */
//    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
//
//    /* Setting DCO to 12MHz */
//    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
//
//    /* Configuring UART Module */
//    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
//
//    /* Enable UART module */
//    MAP_UART_enableModule(EUSCI_A0_BASE);
//
//    /* Enabling interrupts */
//    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
//    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
//    MAP_Interrupt_enableSleepOnIsrExit();
//    MAP_Interrupt_enableMaster();
//
//    importedData = newCircularBuffer(importedData);
//    (importedData->data)[0] = '/';
//
//    while(1)
//    {
//         MAP_PCM_gotoLPM0();
//
//         //memcpy(var, importedData->data, sizeof(uint8_t));
//         //(importedData->data)[0] = '/';
//     }
//}
//
///* EUSCI A0 UART ISR - Echoes data back to PC host */
//void EUSCIA0_IRQHandler(void)
//{
//    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
//
//    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
//    {
//        base = MAP_UART_receiveData(EUSCI_A0_BASE);
//        writeToBuffer(importedData, base);
//        MAP_UART_transmitData(EUSCI_A0_BASE, MAP_UART_receiveData(EUSCI_A0_BASE));
//    }
//
//    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);
//}





























#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 8000

uint8_t word[6];
uint8_t image[8000];

uint8_t base;

//circular buffer
uint8_t data[BUFFER_SIZE];
int head = 0;
int tail = 0;
uint8_t isFullFlag = 0;
uint8_t contentFlag = 0;


int bufferIsFull(){
    return isFullFlag;
}

int bufferIsEmpty(){
    int temp = 0;
    if((head == tail) && (isFullFlag != 1)){
        temp = 1;
    }
    return temp;
}

void writeToBuffer(uint8_t data_element){
    if(bufferIsFull()){
        //do nothing
    }else{
        data[head] = data_element;
        head = (head + 1) % BUFFER_SIZE;
        if(head == tail){
            isFullFlag = 1;
        }
    }
}

void readFromBuffer(){
    if(bufferIsEmpty()){
        //do nothing
    }else{
        //test
        //word[tail] = data[tail];
        if(data[tail] == '|'){
            contentFlag = 1;
        }
        else if(data[tail] == '/'){
            contentFlag = 2;
        }

        if(contentFlag == 1){
            if (data[tail] != '|'){
                word[tail] = data[tail];
            }
        }if(contentFlag == 2){
            if (data[tail] != '/'){
                image[tail] = data[tail];
            }
        }
        tail = (tail + 1) % BUFFER_SIZE;
        isFullFlag = 0;
    }
}

void newCircularBuffer(){
    head = 0;
    tail = 0;
    isFullFlag = 0;
}

void processItem(uint8_t base){
    writeToBuffer(base);
    readFromBuffer();
}

const eUSCI_UART_ConfigV1 uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                       // UCxBRF = 2
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

int main(void)
{
    /*Halt Watchdog Timer*/
    MAP_WDT_A_holdTimer();

    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    /*Initialize Circular Buffer*/
    newCircularBuffer();

    while(1)
    {
         MAP_PCM_gotoLPM0();

     }
}

/* EUSCI A0 UART ISR - Echoes data back to PC host */
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        base = MAP_UART_receiveData(EUSCI_A0_BASE);
        processItem(base);
        MAP_UART_transmitData(EUSCI_A0_BASE, MAP_UART_receiveData(EUSCI_A0_BASE));
    }

    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);
}












