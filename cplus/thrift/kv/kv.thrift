/*
 * Defines kv interface. 
 */

namespace cpp kv

enum ResponseCode 
{
    Success = 0,
    Error,
    KeyNotFound,
}

struct RecordResponse
{
    1:ResponseCode responseCode,
    2:binary value,
}

service kv
{
    /**
     * Pings mapkeeper.
     *
     * @return Success - if ping was successful.
     *         Error - if ping failed.
     */
    ResponseCode ping(),

    /**
     * Retrieves a record from storage.
     *
     * @param key record to retrive.
     * @returns RecordResponse 
     *              responseCode - Ok 
     *                             KeyNotFound key doesn't exist.
     *                             Error on any other errors.
     *              value - value of the record.
     */
    RecordResponse get(1:binary key),

    /**
     * Puts a record into a map.
     *
     * @param key record key to put
     * @param value record value to put
     * @returns Ok 
     *          Error
     */
    ResponseCode put(1:binary key, 2:binary value),

    /**
     * Removes a record from a map.
     *
     * @param key record to remove from the database.
     * @returns Success 
     *          KeyNotFound Key doesn't exist.
     *          Error
     */
    ResponseCode remove(1:binary key),
}
