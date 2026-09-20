cmake_minimum_required(VERSION 3.20)

project(psp_pthread VERSION 2.8.0.0 LANGUAGES C)

option(PSP_PTHREAD_BUILD_TESTS "Build the PSP pthread test application" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(PTHREAD_SOURCES
    cleanup.c
    create.c
    global.c
    pte_callUserDestroyRoutines.c
    pte_cancellable_wait.c
    pte_cond_check_need_init.c
    pte_detach.c
    pte_getprocessors.c
    pte_is_attr.c
    pte_mutex_check_need_init.c
    pte_new.c
    pte_relmillisecs.c
    pte_reuse.c
    pte_rwlock_cancelwrwait.c
    pte_rwlock_check_need_init.c
    pte_spinlock_check_need_init.c
    pte_threadDestroy.c
    pte_threadStart.c
    pte_throw.c
    pte_tkAssocCreate.c
    pte_tkAssocDestroy.c
    pthread_atfork.c
    pthread_attr_destroy.c
    pthread_attr_getdetachstate.c
    pthread_attr_getguardsize.c
    pthread_attr_getinheritsched.c
    pthread_attr_getschedparam.c
    pthread_attr_getschedpolicy.c
    pthread_attr_getscope.c
    pthread_attr_getstack.c
    pthread_attr_getstackaddr.c
    pthread_attr_getstacksize.c
    pthread_attr_init.c
    pthread_attr_setdetachstate.c
    pthread_attr_setguardsize.c
    pthread_attr_setinheritsched.c
    pthread_attr_setschedparam.c
    pthread_attr_setschedpolicy.c
    pthread_attr_setscope.c
    pthread_attr_setstack.c
    pthread_attr_setstackaddr.c
    pthread_attr_setstacksize.c
    pthread_barrier_destroy.c
    pthread_barrier_init.c
    pthread_barrier_wait.c
    pthread_barrierattr_destroy.c
    pthread_barrierattr_getpshared.c
    pthread_barrierattr_init.c
    pthread_barrierattr_setpshared.c
    pthread_cancel.c
    pthread_cond_destroy.c
    pthread_cond_init.c
    pthread_cond_signal.c
    pthread_cond_wait.c
    pthread_condattr_destroy.c
    pthread_condattr_getclock.c
    pthread_condattr_getpshared.c
    pthread_condattr_init.c
    pthread_condattr_setclock.c
    pthread_condattr_setpshared.c
    pthread_delay_np.c
    pthread_detach.c
    pthread_equal.c
    pthread_exit.c
    pthread_getconcurrency.c
    pthread_getschedparam.c
    pthread_getspecific.c
    pthread_init.c
    pthread_join.c
    pthread_key_create.c
    pthread_key_delete.c
    pthread_kill.c
    pthread_mutex_destroy.c
    pthread_mutex_init.c
    pthread_mutex_lock.c
    pthread_mutex_timedlock.c
    pthread_mutex_trylock.c
    pthread_mutex_unlock.c
    pthread_mutexattr_destroy.c
    pthread_mutexattr_getkind_np.c
    pthread_mutexattr_getpshared.c
    pthread_mutexattr_gettype.c
    pthread_mutexattr_init.c
    pthread_mutexattr_setkind_np.c
    pthread_mutexattr_setpshared.c
    pthread_mutexattr_settype.c
    pthread_num_processors_np.c
    pthread_once.c
    pthread_rwlock_destroy.c
    pthread_rwlock_init.c
    pthread_rwlock_rdlock.c
    pthread_rwlock_timedrdlock.c
    pthread_rwlock_timedwrlock.c
    pthread_rwlock_tryrdlock.c
    pthread_rwlock_trywrlock.c
    pthread_rwlock_unlock.c
    pthread_rwlock_wrlock.c
    pthread_rwlockattr_destroy.c
    pthread_rwlockattr_getpshared.c
    pthread_rwlockattr_init.c
    pthread_rwlockattr_setpshared.c
    pthread_self.c
    pthread_setcancelstate.c
    pthread_setcanceltype.c
    pthread_setconcurrency.c
    pthread_setschedparam.c
    pthread_setspecific.c
    pthread_sigmask.c
    pthread_spin_destroy.c
    pthread_spin_init.c
    pthread_spin_lock.c
    pthread_spin_trylock.c
    pthread_spin_unlock.c
    pthread_terminate.c
    pthread_testcancel.c
    pthread_timechange_handler_np.c
    sched_get_priority_max.c
    sched_get_priority_min.c
    sched_setscheduler.c
    sched_yield.c
    sem_close.c
    sem_destroy.c
    sem_getvalue.c
    sem_init.c
    sem_open.c
    sem_post.c
    sem_post_multiple.c
    sem_timedwait.c
    sem_trywait.c
    sem_unlink.c
    sem_wait.c
    platform/helper/tls-helper.c
)

add_library(pthread STATIC ${PTHREAD_SOURCES})

target_include_directories(
    pthread
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/platform/psp>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/helper
)

target_compile_options(
    pthread
    PRIVATE
        -mno-gpopt
        -Wall
        -fno-strict-aliasing
)

# The PSP-specific OS abstraction is supplied by PSPSDK.
target_link_libraries(pthread PUBLIC pthreadglue)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/pthread.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/pthread.pc"
    @ONLY
)

install(
    TARGETS pthread
    ARCHIVE DESTINATION lib
)

install(
    FILES pthread_public.h
    DESTINATION include
    RENAME pthread.h
)

install(
    FILES
        sched.h
        semaphore.h
        platform/psp/pte_types.h
    DESTINATION include
)

install(
    FILES bits/posix_opt.h
    DESTINATION include/bits
)

install(
    FILES
        sys/_pthreadtypes.h
        sys/sched.h
        pte_generic_osal.h
    DESTINATION include/sys
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/pthread.pc"
    DESTINATION lib/pkgconfig
)

if(PSP_PTHREAD_BUILD_TESTS)
    add_executable(
        pthread-test
        platform/psp/main.c
        tests/barrier1.c
        tests/barrier2.c
        tests/barrier3.c
        tests/barrier4.c
        tests/barrier5.c
        tests/benchlib.c
        tests/benchtest1.c
        tests/benchtest2.c
        tests/benchtest3.c
        tests/benchtest4.c
        tests/cancel1.c
        tests/cancel2.c
        tests/cancel3.c
        tests/cancel4.c
        tests/cancel5.c
        tests/cancel6a.c
        tests/cancel6d.c
        tests/cleanup0.c
        tests/cleanup1.c
        tests/cleanup2.c
        tests/cleanup3.c
        tests/condvar1.c
        tests/condvar1_1.c
        tests/condvar1_2.c
        tests/condvar2.c
        tests/condvar2_1.c
        tests/condvar3.c
        tests/condvar3_1.c
        tests/condvar3_2.c
        tests/condvar3_3.c
        tests/condvar4.c
        tests/condvar5.c
        tests/condvar6.c
        tests/condvar7.c
        tests/condvar8.c
        tests/condvar9.c
        tests/count1.c
        tests/create1.c
        tests/create2.c
        tests/create3.c
        tests/delay1.c
        tests/delay2.c
        tests/detach1.c
        tests/equal1.c
        tests/errno1.c
        tests/exception1.c
        tests/exception2.c
        tests/exception3.c
        tests/exit1.c
        tests/exit2.c
        tests/exit3.c
        tests/exit4.c
        tests/exit5.c
        tests/inherit1.c
        tests/join0.c
        tests/join1.c
        tests/join2.c
        tests/join3.c
        tests/join4.c
        tests/kill1.c
        tests/mutex1.c
        tests/mutex1e.c
        tests/mutex1n.c
        tests/mutex1r.c
        tests/mutex2.c
        tests/mutex2e.c
        tests/mutex2r.c
        tests/mutex3.c
        tests/mutex3e.c
        tests/mutex3r.c
        tests/mutex4.c
        tests/mutex5.c
        tests/mutex6.c
        tests/mutex6e.c
        tests/mutex6es.c
        tests/mutex6n.c
        tests/mutex6r.c
        tests/mutex6rs.c
        tests/mutex6s.c
        tests/mutex7.c
        tests/mutex7e.c
        tests/mutex7n.c
        tests/mutex7r.c
        tests/mutex8.c
        tests/mutex8e.c
        tests/mutex8n.c
        tests/mutex8r.c
        tests/mutex9.c
        tests/once1.c
        tests/once2.c
        tests/once3.c
        tests/once4.c
        tests/priority1.c
        tests/priority2.c
        tests/reuse1.c
        tests/rwlock1.c
        tests/rwlock2.c
        tests/rwlock2_t.c
        tests/rwlock3.c
        tests/rwlock3_t.c
        tests/rwlock4.c
        tests/rwlock4_t.c
        tests/rwlock5.c
        tests/rwlock5_t.c
        tests/rwlock6.c
        tests/rwlock6_t.c
        tests/rwlock6_t2.c
        tests/rwlock7.c
        tests/rwlock8.c
        tests/self1.c
        tests/self2.c
        tests/semaphore1.c
        tests/semaphore2.c
        tests/semaphore3.c
        tests/semaphore4.c
        tests/semaphore4t.c
        tests/semaphore5.c
        tests/semaphore6.c
        tests/spin1.c
        tests/spin2.c
        tests/spin3.c
        tests/spin4.c
        tests/stress1.c
        tests/test_main.c
        tests/tsd1.c
        tests/tsd2.c
        tests/valid1.c
        tests/valid2.c
    )

    target_include_directories(
        pthread-test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )

    target_compile_options(
        pthread-test
        PRIVATE
            -mno-gpopt
            -Wall
            -fno-strict-aliasing
    )

    target_link_libraries(
        pthread-test
        PRIVATE
            pthread
            pspdebug
            pspdisplay
            pspge
            pspctrl
    )

    create_pbp_file(
        TARGET pthread-test
        TITLE "PTHREAD TESTS"
    )
endif()
