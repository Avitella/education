/* 1 ------------------------------------------------------------------------------- */
select
  TurnstileRecordID, Date
from
  TurnstileRecord
where
  Status = 1
;

/* 2 ------------------------------------------------------------------------------- */
select
  TurnstileRecordID, Date, Status
from
  TurnstileRecord,
  (
    select
      MetroStationID
    from
      MetroStation
    where
      MetroStation.Name = A
  ) as MetroStation
where
  TurnstileRecord.MetroStationID = MetroStation.MetroStationID and
  TurnstileRecord.Date >= B and TurnstileRecord.Date <= C
;

select
  TurnstileRecordID, Date, Status
from
  TurnstileRecord,
  (
    select
      MetroStationID
    from
      MetroStation
    where
      MetroStation.Name = "Арбатская"
  ) as MetroStation
where
  TurnstileRecord.MetroStationID = MetroStation.MetroStationID and
  TurnstileRecord.Date >= "2014-01-01" and TurnstileRecord.Date <= "2014-06-01"
;

/* 3 ------------------------------------------------------------------------------- */
select
  TurnstileRecordID, Date, Status
from
  TurnstileRecord,
  (
    select
      M.MetroStationID
    from
      MetroStation as M,
      (
        select
          MetroLineID
        from
          MetroLine
        where
          Name = A
      ) as L
    where
      M.MetroLineID = L.MetroLineID
  ) as K
where
  TurnstileRecord.MetroStationID = K.MetroStationID and
  TurnstileRecord.Date >= B and TurnstileRecord.Date <= C
;

select
  TurnstileRecordID, Date, Status
from
  TurnstileRecord,
  (
    select
      M.MetroStationID
    from
      MetroStation as M,
      (
        select
          MetroLineID
        from
          MetroLine
        where
          Name = "Сокольническая линия"
      ) as L
    where
      M.MetroLineID = L.MetroLineID
  ) as K
where
  TurnstileRecord.MetroStationID = K.MetroStationID and
  TurnstileRecord.Date >= "2014-01-01" and TurnstileRecord.Date <= "2014-06-01"
;

/* 4 ------------------------------------------------------------------------------- */
select
  MetroStationID, Name
from
  (
    select
      EndsMetroStationID
    from
      (
        select
          MetroStationID
        from
          MetroStation
        where
          Name = X
      ) as M,
      TransferHub as T
    where
      M.MetroStationID = T.StartsMetroStationID
  ) as C,
  MetroStation as D
where
  C.EndsMetroStationID = D.MetroStationID
;

select
  MetroStationID, Name
from
  (
    select
      EndsMetroStationID
    from
      (
        select
          MetroStationID
        from
          MetroStation
        where
          Name = "Арбатская"
      ) as M,
      TransferHub as T
    where
      M.MetroStationID = T.StartsMetroStationID
  ) as C,
  MetroStation as D
where
  C.EndsMetroStationID = D.MetroStationID
;


/* 5 ------------------------------------------------------------------------------- */
select
  MetroStationID, Name
from
  MetroStation as M,
  (
    select
      MetroLineID
    from
      MetroLine
    where
      Name = X
  ) as L
where
  M.MetroLineID = L.MetroLineID;

select
  MetroStationID, Name
from
  MetroStation as M,
  (
    select
      MetroLineID
    from
      MetroLine
    where
      Name = "Арбатско-Покровская линия"
  ) as L
where
  M.MetroLineID = L.MetroLineID;
