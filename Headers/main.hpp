#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

/* Here is where you write you function prototype */

int socket_send();
void magic_packet(unsigned char macaddress[], unsigned char message[]);
int error_check(int error, string function_name);

#endif // MAIN_HPP_INCLUDED