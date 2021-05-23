#define ShowMessages 0
#include <iostream>
#if ShowMessages
#define MSG(x) std::cout << x << std::endl;
#else
#define MSG(x)
#endif
