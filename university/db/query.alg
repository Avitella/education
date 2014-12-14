R(TurnstileRecordID, Date) =
(
    TurnstileRecord[Status = 1]
)[TurnstileRecordID, Date]

R(TurnstileRecordID, Date, Status) =
(
    (
        TurnstileRecord
            [TurnstileRecord.MetroStationID = MetroStation.MetroStationID]
        (MetroStation[Name = A])
    )[Date >= B & Date <= C]
)[TurnstileRecordID, Date, Status]

R(TurnstileRecordID, Date, Status) =
(
    (
        TurnstileRecord
            [TurnstileRecord.MetroStationID = MetroStation.MetroStationID]
        (
            MetroStation
                [MetroStation.MetroLineID = MetroLine.MetroLineID]
            (MetroLine[Name = A])
        )
    )[Date >= B & Date <= C]
)[TurnstileRecordID, Date, Status]

R(MetroStationID, Name) =
(
    (
        (MetroStation[Name = X])
            [MetroStation.MetroStationID = TransferHub.StartsMetroStationID]
        TransferHub
    )
        [TransferHub.EndsMetroStation = MetroStation.MetroStationID]
    MetroStation
)[MetroStationID, Name]

R(MetroStationID, Name) =
(
    MetroStation
        [MetroStation.MetroLineID = MetroLine.MetroLineID]
    (MetroLine[Name = X])
)[MetroStationID, Name]
