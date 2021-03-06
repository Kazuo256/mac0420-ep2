
#ifndef EP2_EP2_H_
#define EP2_EP2_H_

namespace ep2 {

/// Initializes the program.
/** @param argc Frist parameter from main.
 ** @param argv Second parameter from main.
 ** First arguments are for GLUT. The first non-GLUT argument should be the ones
 ** specified in the README files. */
void init (int argc, char **argv);

/// Runs the program.
void run ();

} // namespace ep2

#endif

