#include <stdio.h>
#include <sys/time.h>

/*
 * ȡ����ǰʱ�����ͺ��룬
 * ���ֱ����Ǳ��浽 seconds �� milliseconds ������
 */
static void aeGetTime(long *seconds, long *milliseconds)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    *seconds = tv.tv_sec;
    *milliseconds = tv.tv_usec/1000;
}

/*
 * Ϊ��ǰʱ����� milliseconds �롣
 */
static void aeAddMillisecondsToNow(long long milliseconds, long *sec, long *ms) {
    long cur_sec, cur_ms, when_sec, when_ms;

    // ��ȡ��ǰʱ��
    aeGetTime(&cur_sec, &cur_ms);

    // �������� milliseconds ֮��������ͺ�����
    when_sec = cur_sec + milliseconds/1000;
    when_ms = cur_ms + milliseconds%1000;

    // ��λ��
    // ��� when_ms ���ڵ��� 1000
    // ��ô�� when_sec ����һ��
    if (when_ms >= 1000) {
        when_sec ++;
        when_ms -= 1000;
    }
    *sec = when_sec;
    *ms = when_ms;
}

/* Return the UNIX time in microseconds */
// ������΢��Ϊ��ʽ�� UNIX ʱ��
long long ustime(void) {
    struct timeval tv;
    long long ust;

    gettimeofday(&tv, NULL);
    ust = ((long long)tv.tv_sec)*1000000;
    ust += tv.tv_usec;
    return ust;
}

/* Return the UNIX time in milliseconds */
// �����Ժ���Ϊ��λ�� UNIX ʱ��
long long mstime(void) {
    return ustime()/1000;
}

#ifdef TEST
int main()
{
    long long milliseconds = 5000000;
    long sec, ms;
    aeAddMillisecondsToNow(milliseconds, &sec, &ms);
    printf("second = %ld, ms = %ld\n", sec, ms);
    return 0;
}
#endif
