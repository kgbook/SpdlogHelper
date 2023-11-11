
A helper library to log like Android log.

## Usage
```cpp
#include "ALog.h"

#define LOG_TAG "Example"

int main(int argc, char **argv) {
    LOGI(LOG_TAG, "Hello!");
    LOGI(LOG_TAG, "Bye!");
    return 0;
}
```

output:
```bash
[2023-11-11 23:26:33.259][pid23288][tid23288][info][Example][main#10]Hello!
[2023-11-11 23:26:33.259][pid23288][tid23288][info][Example][main#11]Bye!
```