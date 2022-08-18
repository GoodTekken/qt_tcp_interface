# **TCP**通信协议**V1.0**

[TOC]

## 项目链接

Github:https://github.com/GoodTekken/qt_tcp_interface

## 历史版本

| **版本** | **日期**   | **修订内容** | **作者**                                                   |
| -------- | ---------- | ------------ | ---------------------------------------------------------- |
| V1.0     | 2022/08/27 | 文档创建     | [吕凯盛](https://github.com/aozaki-touko/qt_tcp_interface) |
|          |            |              |                                                            |
|          |            |              |                                                            |
|          |            |              |                                                            |
|          |            |              |                                                            |
|          |            |              |                                                            |

## 1.简介

### 1.1通信IP与通信端口

​		PDS是以守护进程的方式直接运行在IFM O3D303相机上的，相机的默认IP是192.168.0.69，PDS系统监听55555端口，在应用层上，PDS是采用TCP通信协议进行通信的。全部的数据字节序都是大端（即网络所使用的字节序）

**注:除非特别指明，否则本文使用的距离单位均为米，角度单位均为弧度，坐标系均为右手系，坐标原点为相机镜片中心**

## 2.通信协议介绍

| **报文类型**       | **功能**                             |
| ------------------ | ------------------------------------ |
| NOOP               | 无操作，可以用于确认是否连接（心跳） |
| GETPALLET          | NDC对于订单状态的通知。              |
| GetArray           | NDC向Host请求或确认同步信息。        |
| SaveReferenceForks | Host删除任务（根据索引或车辆ID）     |
| GetRack            | Host回复Message_s的信号。            |
| VolCheck           |                                      |
| GetConfig          |                                      |
| SetConfig          |                                      |
| SaveConfig         |                                      |
| ResetConfig        |                                      |
| SaveExtrinsics     |                                      |

### 2.1 NOOP定义

| **作用** | **无操作，可以用于确认是否连接（心跳）**                     |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start(‘star’),cmd_id(0),arg_len(0),seq_end(“stop\n\r”) |
|          | Response:   Seq_start(‘star’),cmd_id(0),status(0 正常,错误码位于附录), len(6),seq_end(“stop\n\r”) |
| **备注** | **具体的数据类型位于下表**                                   |

**request**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 0                                        |
| 8 – 11  | arg_lens   |           | uint32   | 0                                        |
| 12 – 17 | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**response**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 0                                        |
| 8 – 11  | status     |           | int32    | 0或其他错误                              |
| 12 – 15 | len        |           | uint32   | 6                                        |
| 16-21   | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

### **2.2 GetPallet定义**

| **作用** | **客户端向服务端获取托盘位置。服务端返回一个**6自由度的托盘姿体 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request：  Seq_start,cmd_id(1),arg_len,pallet_type,depth_hint,filter_mask ,seq_end |
|          | Response:  Seq_start,cmd_id(1),status(附录),  len,payload,seq_end |
| **备注** | **仅能识别**2个洞口的托盘                                    |

Request:

| 字节   | Field       | 数据类型 | 数据                                                         |
| ------ | ----------- | -------- | ------------------------------------------------------------ |
| 0 – 3  | seq_start   | uint8[4] | (115, 116, 97, 114)即("star")                                |
| 4 – 7  | command_id  | uint32   | 1                                                            |
| 8 – 11 | arg_len     | uint32   | 7                                                            |
| 12-13  | pallet_type | uint16   | (1 = CHEP_FRONT, 2=CHEP_SIDE,  3=GMA, 4=BLOCK, 5=STRINGER,  6=COMPOSED_BLOCK) |
| 14-17  | depth_hint  | float32  | 从相机中获取的深度                                           |
| 18     | filter_mask | uint8    | 0 = stray light filter 1 = fast flying pixel filter 2 = stretch wrap filter |
| 19-24  | seq_end     | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r"                     |

掩膜三类(机翻,不能保证正确性)

0. 检测源点云中的杂散光像素，并在运行管道之前将其过滤掉。通常在存在导航后向反射器、高光泽地板或高反射负载时很有用。推荐默认值：关闭
1. 与标准（非常稳健）的 SOR 滤波器相比，将运行计算速度快（尽管不太稳健）的飞行像素滤波器来过滤飞行像素。有关详细信息和使用指南，请参阅比较 SOR 与 FFP 性能的文档。推荐默认值：关闭
2. 一种预处理过滤器，专门针对由拉伸包裹引起的伪影。在 SOR 之前运行。不适用于 FFP 过滤器。有关详细信息，请参阅拉伸包装过滤器应用说明。推荐默认值：关闭
3. 3-7为未使用的

Response:**此处坐标均在相机帧**

| 字节    | Field      | sub-Field      | 数据类型 | 数据                                     |
| ------- | ---------- | -------------- | -------- | ---------------------------------------- |
| 0 – 3   | seq_start  |                | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |                | uint32   | 1                                        |
| 8 – 11  | status     |                | int32    | 0或其他错误                              |
| 12 – 15 | len        |                | uint32   | 6+payload的字节数                        |
| 16-19   | payload    | elapse_time    | float32  | 检测所需时间                             |
| 20-23   |            | confidence     | float32  |                                          |
| 24-27   |            | pallet_x       | float32  | 相机的帧中托盘的x坐标                    |
| 28-31   |            | pallet_y       | float32  | 相机的帧中托盘的y坐标                    |
| 32-35   |            | pallet_z       | float32  | 相机的帧中托盘的z坐标                    |
| 36-39   |            | left_pocket_x  | float32  | 左洞口x坐标                              |
| 40-43   |            | left_pocket_y  | float32  | 左洞口y坐标                              |
| 44-47   |            | left_pocket_z  | float32  | 左洞口z坐标                              |
| 48-51   |            | right_pocket_x | float32  | 右洞口x坐标                              |
| 52-55   |            | right_pocket_y | float32  | 右洞口y坐标                              |
| 56-59   |            | right_pocket_z | float32  | 右洞口z坐标                              |
| 60-63   |            | roll           | float32  | 绕相机坐标系x轴旋转的弧度                |
| 64-67   |            | pitch          | float32  | 绕相机坐标系y轴旋转的弧度                |
| 68-71   |            | yaw            | float32  | 绕相机坐标系z轴旋转的弧度                |
| 72-77   | seq_end    |                | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**可能会返回一个指示 6 字节响应的“Len”字段，在这种情况下，有效负载将被忽略，并且数据包的其余部分将仅包含“Stop”序列'。(即出错)**

### 2.3 GetArray Command

| **作用** | 向 PDS 发出请求以返回与在当前连接的套接字上进行的最后一次 PDS 检测尝试相关联的数组数据。 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request：  Seq_start,cmd_id(2),arg_len(4), array_id,seq_end  |
|          | Response:  Seq_start,cmd_id(1),status(附录), len,payload ,seq_end |
| **备注** | 注意：GetArray 调用返回与拾取端或放置端检测相关的数组数据。 此调用在使用上是先进的，应被视为用于调试或可视化目的的“反向通道”。 |

**response**

| 字节   | Field      | sub-Field | 数据类型 | 数据                                     |
| ------ | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3  | seq_start  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7  | command_id |           | uint32   | 2                                        |
| 8 – 11 | arg_len    |           | uint32   | 4                                        |
| 12-15  | array_id   |           | uint32   | 见下方                                   |
| 16-21  | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**request**

| 字节数      | Field      | sub-Field  | 数据类型     | 数据                                                         |
| ----------- | ---------- | ---------- | ------------ | ------------------------------------------------------------ |
| 4           | seq_start  |            | uint8[4]     | (115, 116, 97, 114)即("star")                                |
| 4           | command_id |            | uint32       | 2                                                            |
| 4           | status     |            | int32        | 0或其他错误                                                  |
| 4           | len        |            | uint32       | 6+payload的字节数                                            |
| 4           | payload    | rows       | int32        | 数据行数                                                     |
| 4           |            | cols       | int32        | 数据列数                                                     |
| 4           |            | channels   | int32        | 数组数据中的通道数                                           |
| 4           |            | pixel_type | int32        | 附录                                                         |
| 长度码-16-6 |            | pixel_data | PixelType[N] | 这些像素数据以行优先顺序返回。 因此，使用子标题，这些像素数据可以在套接字的接收端适当地重新变形。 |
| 6           | seq_end    |            | uint8[6]     | (115, 116, 111, 112, 13, 10)即"stop\n\r"                     |

### 2.4 SaveReferenceForks Command

| **作用** | 向 PDS 发出请求以序列化参考叉的图像，以执行校准外检查。 |
| -------- | ------------------------------------------------------- |
| **格式** | Request:   Seq_start,cmd_id,arg_len,seq_end             |
|          | Response:   Seq_start,cmd_idstatus, len,seq_end         |
| **备注** | **具体的数据类型位于下表**                              |

**request**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | seq_start  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 3                                        |
| 8 – 11  | arg_len    |           | uint32   | 0                                        |
| 12 – 17 | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**response**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | seq_start  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 3                                        |
| 8 – 11  | status     |           | int32    | 0或其他错误                              |
| 12 – 15 | len        |           | uint32   | 6                                        |
| 16-21   | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

### 2.5 GetRack Command

| **作用** | 获取支架位置                                                 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,HDP,VDP,camera_pos,depth_hint,z_hint,clearing_depth,clearing_width,filter,seq_end |
|          | Response:   Seq_start,cmd_id,status, len,seq_end             |
| **备注** | **具体的数据类型位于下表**                                   |