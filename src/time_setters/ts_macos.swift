import Foundation
enum StringArgumentError : Error {
    case invalidDateFormat
}

// C wrapper
@_cdecl("set_timestamp")
public func setTimestampFromCString(_ nullTerminatedPath: UnsafePointer<CChar>,
    _ nullTerminatedDate : UnsafePointer<CChar>) -> Int32 {
    let filePath = String(cString: nullTerminatedPath)
    let dateString = String(cString: nullTerminatedDate)
    do {
        try setFileTime(filePath, date: dateString)
        return 0;
    } catch StringArgumentError.invalidDateFormat {
        print("Provided date wasn't parsed")
        return 1;
    } catch {
        print(error.localizedDescription)
        return 1;
    }
}

func setFileTime(_ filePath: String, date: String) throws {
    guard let newDate = stringToNSDate(date, format: "yyyy/MM/dd HH:mm:ss") else {
        throw StringArgumentError.invalidDateFormat
    }
    let timeAttributes = [
        FileAttributeKey.creationDate : newDate,
        FileAttributeKey.modificationDate : newDate,
    ]
    try FileManager.default.setAttributes(timeAttributes, ofItemAtPath: filePath)
}

func stringToNSDate(_ dateString : String ,format : String) -> NSDate? {
    let dateFormater = DateFormatter()
    dateFormater.dateFormat = format

    guard let date = dateFormater.date(from: dateString) else {
        return nil
    }
    let nsdate = date as NSDate

    return nsdate
}
