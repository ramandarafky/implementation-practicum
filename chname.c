/* chname.c - chname */

#include <xinu.h>

/*------------------------------------------------------
 * chname - Dummy syscall
 *------------------------------------------------------
 */

pri16 chname(
    pid32 pid,        /* ID of process to change */
    pri16 newprio     /* New priority */
)
{
    intmask mask;             /* Saved interrupt mask */
    struct procent *prptr;    /* Ptr to process's table entry */
    pri16 oldprio;            /* Priority to return */

    mask = disable();
    if (isbadpid(pid)) {
        restore(mask);
        return (pri16) SYSERR;
    }

    prptr = &proctab[pid];
    oldprio = prptr->prprio;
    prptr->prprio = newprio;
    kprintf("\n\nNew Syscall is easy\n\n");
    restore(mask);
    return oldprio;
}
