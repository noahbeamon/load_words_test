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




























/////////////----------------------------Working Copy------------------/////////////
//#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//#define BUFFER_SIZE 8000
//
//uint8_t base;
//
////circular buffer
//uint8_t data[BUFFER_SIZE];
//int head = 0;
//int tail = 0;
//uint8_t isFullFlag = 0;
//uint8_t contentFlag = 0;
//
//
//int bufferIsFull(){
//    return isFullFlag;
//}
//
//int bufferIsEmpty(){
//    int temp = 0;
//    if((head == tail) && (isFullFlag != 1)){
//        temp = 1;
//    }
//    return temp;
//}
//
//void writeToBuffer(uint8_t data_element){
//    if(bufferIsFull()){
//        //do nothing
//    }else{
//        data[head] = data_element;
//        head = (head + 1) % BUFFER_SIZE;
//        if(head == tail){
//            isFullFlag = 1;
//        }
//    }
//}
//
//char word[5];
//int wordIndex = 0;
//
//uint8_t image[8000];
//int imageIndex = 0;
//
//char imageType[4];
//int imageTypeIndex = 0;
//
//char imageSizeTemp[4];
//int imageSizeTempIndex = 0;
//int imageSize = 0;
//
//char imageWidthTemp[3];
//int imageWidthTempIndex = 0;
//int imageWidth = 0;
//
//char imageHeightTemp[3];
//int imageHeightTempIndex = 0;
//int imageHeight = 0;
//
//int imageArray[8000];
//int imageArrayIndex = 0;
//
//void readFromBuffer(){
//    if(bufferIsEmpty()){
//        //do nothing
//    }else{
//        //test
//        //word[tail] = data[tail];
//        if(data[tail] == '|'){
//            contentFlag = 1;
//        }
//        else if(data[tail] == '/'){
//            contentFlag = 2;
//        }
//        else if(data[tail] == '$'){
//            contentFlag = 3;
//        }
//        else if(data[tail] == '*'){
//            contentFlag = 4;
//        }
//        else if(data[tail] == '#'){
//            contentFlag = 5;
//        }
//        else if(data[tail] == '!'){
//            contentFlag = 6;
//        }
//        else if(data[tail] == '%'){
//            contentFlag = 7;
//        }
//
//        if(contentFlag == 1 && data[tail] != '|'){
//            word[wordIndex] = data[tail];
//            wordIndex++;
//        }if(contentFlag == 2 && data[tail] != '/'){
//            image[imageIndex] = data[tail];
//            imageIndex++;
//        }
//        if(contentFlag == 3 && data[tail] != '$'){
//            imageType[imageTypeIndex] = data[tail];
//            imageTypeIndex++;
//        }
//        if(contentFlag == 4 && data[tail] != '*'){
//            imageSizeTemp[imageSizeTempIndex] = data[tail];
//            imageSizeTempIndex++;
//            imageSize = atoi(imageSizeTemp);
//        }
//        if(contentFlag == 5 && data[tail] != '#'){
//            imageWidthTemp[imageWidthTempIndex] = data[tail];
//            imageWidthTempIndex++;
//            imageWidth = atoi(imageWidthTemp);
//        }
//        if(contentFlag == 6 && data[tail] != '!'){
//            imageHeightTemp[imageHeightTempIndex] = data[tail];
//            imageHeightTempIndex++;
//            imageHeight = atoi(imageHeightTemp);
//        }
//        if(contentFlag == 7){
//            int i;
//            int tempIndex = 0;
//            int tempNum;
//            imageArrayIndex = 0;
//
//            for (i = 0; i < sizeof(image)/sizeof(image[0]); i++){
//                char temp[4];
//                if(image[i] != ','){
//                    temp[tempIndex] = image[i];
//                    tempIndex++;
//                }
//                if(image[i] == ',' || image[i] == NULL ){
//                    tempNum = atoi(temp);
//                    imageArray[imageArrayIndex] = tempNum;
//                    imageArrayIndex++;
//
//                    int j;
//                    for(j = 0; j < 4; j++){
//                        temp[j] = NULL;
//                    }
//                    tempIndex = 0;
//                }
//            }
//            //clear everything
////            int k;
////            for (k = 0; k < 8000; k++){
////                data[k] = NULL;
////                image[k] = NULL;
////                imageArray[k] = NULL;
////            }
////            head = 0;
////            tail = 0;
////            isFullFlag = 0;
////            contentFlag = 0;
////
////            int t;
////            for(t = 0; t < 5; t++){
////                word[t] = NULL;
////            }
////
////            wordIndex = 0;
////
////            imageIndex = 0;
////
////            int q;
////            for(q = 0; q < 4; q++){
////                imageType[q] = NULL;
////                imageSizeTemp[q] = NULL;
////            }
////
////            imageTypeIndex = 0;
////
////            imageSizeTempIndex = 0;
////            imageSize = 0;
////
////            int y;
////            for(y = 0; y < 3; y++){
////                imageWidthTemp[y] = NULL;
////                imageHeightTemp[y] = NULL;
////            }
////
////            imageWidthTempIndex = 0;
////            imageWidth = 0;
////
////            imageHeightTempIndex = 0;
////            imageHeight = 0;
////
////            imageArrayIndex = 0;
//            tail = 0;
//        }
////        tail = (tail + 1) % BUFFER_SIZE;
////        isFullFlag = 0;
//        tail+=1;
//    }
//}
//
//void processItem(uint8_t base){
//    writeToBuffer(base);
//    readFromBuffer();
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
//    while(1)
//    {
//         MAP_PCM_gotoLPM0();
//
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
//        processItem(base);
//        MAP_UART_transmitData(EUSCI_A0_BASE, MAP_UART_receiveData(EUSCI_A0_BASE));
//    }
//
//    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);
//}










///////////----------------------------Working Copy------------------/////////////
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct image_properties{
    uint8_t height;
    uint8_t width;
    uint32_t image_size;
    char image_type[4];
    char image_word[5]; //max length of words
    //uint8_t * image[];
};

struct image_properties dictionary[32];

uint8_t dictionaryIndex = 0;

#define BUFFER_SIZE 8000

uint8_t base;

//circular buffer
uint8_t data[BUFFER_SIZE];
int head = 0;
int tail = 0;
uint8_t contentFlag = 0;

void writeToBuffer(uint8_t data_element, int head){
    data[head] = data_element;
}

char word[5];
int wordIndex = 0;

uint8_t image[8000];
int imageIndex = 0;

char imageType[4];
int imageTypeIndex = 0;

char imageSizeTemp[4];
int imageSizeTempIndex = 0;
int imageSize = 0;

char imageWidthTemp[3];
int imageWidthTempIndex = 0;
int imageWidth = 0;

char imageHeightTemp[3];
int imageHeightTempIndex = 0;
int imageHeight = 0;

int imageArray[8000];
int imageArrayIndex = 0;

void readFromBuffer(int tail){
    if(data[tail] == '|'){
        contentFlag = 1;
    }
    else if(data[tail] == '/'){
        contentFlag = 2;
    }
    else if(data[tail] == '$'){
        contentFlag = 3;
    }
    else if(data[tail] == '*'){
        contentFlag = 4;
    }
    else if(data[tail] == '#'){
        contentFlag = 5;
    }
    else if(data[tail] == '!'){
        contentFlag = 6;
    }
    else if(data[tail] == '%'){
        contentFlag = 7;
    }

    if(contentFlag == 1 && data[tail] != '|'){
        word[wordIndex] = data[tail];
        wordIndex++;
    }if(contentFlag == 2 && data[tail] != '/'){
        image[imageIndex] = data[tail];
        imageIndex++;
    }
    if(contentFlag == 3 && data[tail] != '$'){
        imageType[imageTypeIndex] = data[tail];
        imageTypeIndex++;
    }
    if(contentFlag == 4 && data[tail] != '*'){
        imageSizeTemp[imageSizeTempIndex] = data[tail];
        imageSizeTempIndex++;
        imageSize = atoi(imageSizeTemp);
    }
    if(contentFlag == 5 && data[tail] != '#'){
        imageWidthTemp[imageWidthTempIndex] = data[tail];
        imageWidthTempIndex++;
        imageWidth = atoi(imageWidthTemp);
    }
    if(contentFlag == 6 && data[tail] != '!'){
        imageHeightTemp[imageHeightTempIndex] = data[tail];
        imageHeightTempIndex++;
        imageHeight = atoi(imageHeightTemp);
    }
    if(contentFlag == 7){
        int i;
        int tempIndex = 0;
        int tempNum;
        imageArrayIndex = 0;

        for (i = 0; i < sizeof(image)/sizeof(image[0]); i++){
            char temp[4];
            if(image[i] != ','){
                temp[tempIndex] = image[i];
                tempIndex++;
            }
            if(image[i] == ',' || image[i] == NULL ){
                tempNum = atoi(temp);
                imageArray[imageArrayIndex] = tempNum;
                imageArrayIndex++;

                int j;
                for(j = 0; j < 4; j++){
                    temp[j] = NULL;
                }
                tempIndex = 0;
            }
        }
    }
}

void processItem(uint8_t base){
    if(base == '+'){
        return;
    }
    writeToBuffer(base, head);
    readFromBuffer(tail);
    if(base == '%'){
        //send ack
        MAP_UART_transmitData(EUSCI_A0_BASE, 'k');
        //set image properties
        struct image_properties tempImageProps;
        tempImageProps.height = imageHeight;
        tempImageProps.width = imageWidth;
        tempImageProps.image_size = imageSize;
        strcpy(tempImageProps.image_type, imageType);
        strcpy(tempImageProps.image_word, word);
        dictionary[dictionaryIndex] = tempImageProps;
        if(dictionaryIndex == 31){
            dictionaryIndex = 0;
        }else{
            dictionaryIndex++;
        }
        //flash image to memory
        //FlashCtl_programMemory(void* src, void* dest, uint32_t length);
        FlashCtl_programMemory((void*) imageArray, (void*) FLASH_SECTOR0, sizeof(imageArray));
        //reset head and tail
        head = 0;
        tail = 0;
        //clear everything
        int j = 0;
        for (j = 0; j < 8000; j++){
            data[j] = NULL;
        }
         int k;
         for (k = 0; k < 8000; k++){
             data[k] = NULL;
             image[k] = NULL;
             imageArray[k] = NULL;
         }

         int t;
         for(t = 0; t < 5; t++){
             word[t] = NULL;
         }

         wordIndex = 0;

         imageIndex = 0;

         int q;
         for(q = 0; q < 4; q++){
             imageType[q] = NULL;
             imageSizeTemp[q] = NULL;
         }

         imageTypeIndex = 0;

         imageSizeTempIndex = 0;
         imageSize = 0;

         int y;
         for(y = 0; y < 3; y++){
             imageWidthTemp[y] = NULL;
             imageHeightTemp[y] = NULL;
         }

         imageWidthTempIndex = 0;
         imageWidth = 0;

         imageHeightTempIndex = 0;
         imageHeight = 0;

         imageArrayIndex = 0;
    }else{
        head++;
        tail++;
    }
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
        //MAP_UART_transmitData(EUSCI_A0_BASE, MAP_UART_receiveData(EUSCI_A0_BASE));
    }

    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);
}


