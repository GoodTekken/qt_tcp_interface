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

| **作用** | **客户端向服务端获取托盘位置。服务端返回一个**6自由度的托盘面 |
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

**request**

| 字节   | Field      | sub-Field | 数据类型 | 数据                                     |
| ------ | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3  | seq_start  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7  | command_id |           | uint32   | 2                                        |
| 8 – 11 | arg_len    |           | uint32   | 4                                        |
| 12-15  | array_id   |           | uint32   | 见下方                                   |
| 16-21  | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |
**response**


| 字节数   | Field      | sub-Field  | 数据类型     | 数据                                                         |
| -------- | ---------- | ---------- | ------------ | ------------------------------------------------------------ |
| 4        | seq_start  |            | uint8[4]     | (115, 116, 97, 114)即("star")                                |
| 4        | command_id |            | uint32       | 2                                                            |
| 4        | status     |            | int32        | 0或其他错误                                                  |
| 4        | len        |            | uint32       | 6+payload的字节数                                            |
| 4        | payload    | rows       | int32        | 数据行数                                                     |
| 4        |            | cols       | int32        | 数据列数                                                     |
| 4        |            | channels   | int32        | 数组数据中的通道数                                           |
| 4        |            | pixel_type | int32        | 附录                                                         |
| len-16-6 |            | pixel_data | PixelType[N] | 这些像素数据以行优先顺序返回。 因此，使用子标题，这些像素数据可以在套接字的接收端适当地重新变形。 |
| 6        | seq_end    |            | uint8[6]     | (115, 116, 111, 112, 13, 10)即"stop\n\r"                     |

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
| **格式** | Request:   Seq_start,cmd_id,arg_len,HDP,VDP,camera_pos,depth_hint,z_hint,clearing_depth,clearing_width,clearing_height,filter,seq_end |
|          | Response:   Seq_start,cmd_id,status, len,payload,seq_end     |
| **备注** | **运行正常时返回的是正常的payload，发生错误payload为空**     |

**request**

| 字节   | Field               | sub-Field | 数据类型 | 数据                                             |
| ------ | ------------------- | --------- | -------- | ------------------------------------------------ |
| 0 – 3  | seq_start           |           | uint8[4] | (115, 116, 97, 114)即("star")                    |
| 4 – 7  | command_id          |           | uint32   | 4                                                |
| 8 – 11 | arg_len             |           | uint32   | 24                                               |
| 12     | horizontal_drop_pos |           | uint8    | 0-左，1-中间，2-右                               |
| 13     | vertical_drop_pos   |           | uint8    | 0-顶端，1-内部，2-底部轨道，3-地板               |
| 14     | camera_pos          |           | uint8    | 0 = FULL_UP 1 = FULL_DOWN(不太明白)              |
| 15-18  | depth_hint          |           | float32  | 货架表面到相机玻璃距离                           |
| 19-22  | Z_hint              |           | float32  | 货架在相机帧中z坐标的估计                        |
| 23-26  | clearing_depth      |           | float32  | +x 方向与原点没有障碍物的距离                    |
| 27-30  | clearing_width      |           | float32  | y方向与原点没有障碍物的距离,右移则为+，左移则为- |
| 31-34  | clearing_height     |           | float32  | +z 方向与原点没有障碍物的距离                    |
| 35     | stray_light_filter  |           | uint8    | 0不使用，1使用                                   |
| 36-41  | seq_end             |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r"         |
|        |                     |           |          |                                                  |

**response**

| 字节    | Field      | sub-Field   | 数据类型 | 数据                                            |
| ------- | ---------- | ----------- | -------- | ----------------------------------------------- |
| 0 – 3   | seq_start  |             | uint8[4] | (115, 116, 97, 114)即("star")                   |
| 4 – 7   | command_id |             | uint32   | 4                                               |
| 8 – 11  | status     |             | int32    | 0或其他错误                                     |
| 12 – 15 | len        |             | uint32   | payload+seq_end                                 |
| 16-19   | payload    | elapse_time | float32  | 检测所需时间                                    |
| 20-23   |            | confidence  | float32  | 可靠度                                          |
| 24-27   |            | X           | float32  | 支架在相机帧中的x坐标                           |
| 28-31   |            | Y           | float32  | 支架在相机帧中的y坐标                           |
| 32-35   |            | Z           | float32  | 支架在相机帧中的z坐标                           |
| 36-39   |            | roll        | float32  | 支架在x轴旋转弧度                               |
| 40-43   |            | pitch       | float32  | 支架在y轴旋转弧度                               |
| 44-47   |            | yaw         | float32  | 支架在z轴旋转弧度                               |
| 48      |            | side        | uint8    | 相机帧所在的一侧 0-左，1-中间(一般不发生)，2-右 |
| 49-52   |            | flags       | uint32   | 见下表                                          |
| 53-58   | seq_end    |             | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r"        |

**Flags详解**

| 数值  | 名字             | description                                                  |
| ----- | ---------------- | ------------------------------------------------------------ |
| 0     | NO_BEAM          | 货架网格位置的水平梁无法分割（这是一个“硬”错误）             |
| 1     | MULTIPLE_BEAM    | 多条横梁被分割，取最佳的(最上面的)                           |
| 2     | BEAM_COVERAGE    | 横梁上的像素覆盖阈值未达到                                   |
| 3     | NO_UPRIGHT       | 未检测到垂直立柱，根据分段梁、扫描体积和（可选）地板建立机架框架 |
| 4     | MULTIPLE_UPRIGHT | 多条(在感兴趣的一侧)立柱被分割，最佳的一条被检测             |
| 5     | UPRIGHT_COVERAGE | 立柱上的像素覆盖阈值未达到                                   |
| 6     | NO_JOIN          | 用于建立机架框架的梁和立柱在点云中不相交                     |
| 7     | BAD_TRANSFORM    | 计算出的机架框架的原点超出了预期的容差（表示仅梁定位锚定到障碍物） |
| 8     | SHELF_OBSTACLE   | 相对于已建立的货架框架，在货架扫描空间内检测到障碍物         |
| 9     | BAD_SHELF_LIMITS | 用户提供的清除量参数无效，默认值（配置文件中的值）用于检测障碍物 |
| 10-31 | 预留             |                                                              |

### 2.6 VolCheck Command

| **作用** | 检查一片空间是否有障碍物，此命令对于在实际放置负载之前检查障碍物的块堆叠下降很有用。 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,xmin,xmax,ymin,ymax,zmin,zmax,filter,seq_end |
|          | Response:   Seq_start,cmd_id,status, len,elapsed_time,Npix,seq_end |
| **备注** | **障碍物的概念由主 PDS 配置文件中的像素计数阈值定义。 需要注意的是，这个检查是在相机帧中进行的，所以，相机方向一般应该是rpy = <0,0,0>。** |

**request**

| 字节   | Field              | sub-Field | 数据类型 | 数据                                     |
| ------ | ------------------ | --------- | -------- | ---------------------------------------- |
| 0 – 3  | seq_start          |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7  | command_id         |           | uint32   | 5                                        |
| 8 – 11 | arg_len            |           | uint32   | 25                                       |
| 12-15  | xmin               |           | float32  | 搜索区域x最小值(在相机帧)                |
| 16-19  | xmax               |           | float32  | 搜索区域x最大值(在相机帧)                |
| 20-23  | ymin               |           | float32  | 搜索区域y最小值(在相机帧)                |
| 24-27  | ymax               |           | float32  | 搜索区域y最大值(在相机帧)                |
| 28-31  | zmin               |           | float32  | 搜索区域z最小值(在相机帧)                |
| 32-35  | zmax               |           | float32  | 搜索区域z最大值(在相机帧)                |
| 36     | stray_light_filter |           | uint8    | 0不使用，1使用                           |
| 37-42  | seq_end            |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |
|        |                    |           |          |                                          |

**response**

| 字节    | Field       | sub-Field | 数据类型 | 数据                                                         |
| ------- | ----------- | --------- | -------- | ------------------------------------------------------------ |
| 0 – 3   | seq_start   |           | uint8[4] | (115, 116, 97, 114)即("star")                                |
| 4 – 7   | command_id  |           | uint32   | 5                                                            |
| 8 – 11  | status      |           | int32    | 0，若 npix 超过配置的阈值则返回PDS_VOL_CHECK_OBST,否则其他错误 |
| 12 – 15 | len         |           | uint32   | 8                                                            |
| 16-19   | elapse_time |           | float32  | 检测时间                                                     |
| 20-23   | Npix        |           | int32    | 检测区域的像素(应该是指障碍物的)                             |
| 24-29   | seq_end     |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r"                     |
|         |             |           |          |                                                              |

### 2.7 GetConfig Command

| **作用** | 向 PDS 发出请求以返回序列化的配置数据。                      |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,seq_end                  |
|          | Response:   Seq_start,cmd_id,status, len,payload,seq_end     |
| **备注** | 注意：此调用被视为高级用法，只能在 ifm 支持工程师的指导下使用。 |

**request**

| 字节   | Field      | sub-Field | 数据类型 | 数据                                     |
| ------ | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3  | seq_start  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7  | command_id |           | uint32   | 7                                        |
| 8 – 11 | arg_len    |           | uint32   | 0                                        |
| 12-17  | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**response**

| 字节数 | Field      | sub-Field | 数据类型     | 数据                                     |
| ------ | ---------- | --------- | ------------ | ---------------------------------------- |
| 4      | seq_start  |           | uint8[4]     | (115, 116, 97, 114)即("star")            |
| 4      | command_id |           | uint32       | 7                                        |
| 4      | status     |           | int32        | 0或其他错误                              |
| 4      | len        |           | uint32       | payload+seq_end                          |
| len-6  | payload    |           | uint8[len-6] | 一个包含配置信息的字节数组               |
| 6      | seq_end    |           | uint8[6]     | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

### 2.8 SetConfig Command

| **作用** | 请求 PDS 使用提供的配置信息更新当前配置信息。 通过此请求进行的更新不会在设备重新启动后保留 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,config_data,seq_end      |
|          | Response:   Seq_start,cmd_id,status, len,seq_end             |
| **备注** | 注意：此调用被视为高级用法，只能在 ifm 支持工程师的指导下使用。 |

**request**

| 字节              | Field              | sub-Field | 数据类型 | 数据                                     |
| ----------------- | ------------------ | --------- | -------- | ---------------------------------------- |
| 0 – 3             | seq_start          |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7             | command_id         |           | uint32   | 8                                        |
| 8 – 11            | arg_len            |           | uint32   | N <sizeof config data is bytes>          |
| 12 – (12+N-1)     | Configuration_Data |           | uint8[N] | 包含结构化配置数据的字节数组             |
| (12+N) – (12+N+5) | seq_end            |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**response**

| 字节数 | Field      | sub-Field | 数据类型 | 数据                                     |
| ------ | ---------- | --------- | -------- | ---------------------------------------- |
| 0-3    | seq_start  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4-7    | command_id |           | uint32   | 8                                        |
| 8-11   | status     |           | int32    | 0或其他错误                              |
| 12-15  | len        |           | uint32   | 6                                        |
| 16-21  | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

### 2.9 SaveConfig Command

| **作用** | 请求 PDS 将当前加载的配置保存到文件系统，覆盖以前的配置数据。 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,seq_end                  |
|          | Response:   Seq_start,cmd_id,status, len,seq_end             |
| **备注** | 注意：此调用会永久更改保存在嵌入式设备上的配置数据的状态。 谨慎使用。 |

**request**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 9                                        |
| 8 – 11  | arg_lens   |           | uint32   | 0                                        |
| 12 – 17 | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**response**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 9                                        |
| 8 – 11  | status     |           | int32    | 0或其他错误                              |
| 12 – 15 | len        |           | uint32   | 6                                        |
| 16-21   | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

### 2.10 ResetConfig Command

| **作用** | 请求 PDS 恢复出厂配置数据。 恢复的配置数据必须重启设备才能生效。 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,seq_end                  |
|          | Response:   Seq_start,cmd_id,status, len,seq_end             |
| **备注** | 此调用永久更改保存在嵌入式设备上的配置数据的状态             |

**request**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 10                                       |
| 8 – 11  | arg_lens   |           | uint32   | 0                                        |
| 12 – 17 | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

**response**

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 10                                       |
| 8 – 11  | status     |           | int32    | 0或其他错误                              |
| 12 – 15 | len        |           | uint32   | 6                                        |
| 16-21   | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

### 2.11 SaveExtrinsics Command

| **作用** | SaveExtrinsics 命令允许客户端在设备上运行的 PDS 守护程序中存储外部变换信息（相机在选择的全局坐标系中的姿势）。 |
| -------- | ------------------------------------------------------------ |
| **格式** | Request:   Seq_start,cmd_id,arg_len,x,y,z,roll,pitch,yaw,seq_end |
|          | Response:   Seq_start,cmd_id,status, len,seq_end             |
| **备注** | PDS 算法不以任何方式使用这种转换：这只是为了方便起见的持久存储机制。 可以使用 GetArray 为 EXTRINSICS 数组 ID.gineer 检索保存的外部信息。 |

request

| 字节   | Field      | sub-Field | 数据类型 | 数据                                     |
| ------ | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3  | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7  | command_id |           | uint32   | 11                                       |
| 8 – 11 | arg_lens   |           | uint32   | 24                                       |
| 12-15  | x          |           | float32  | 相机的x位置(在用户定义的坐标系下)        |
| 16-19  | y          |           | float32  | 相机的y位置(在用户定义的坐标系下)        |
| 20-23  | z          |           | float32  | 相机的z位置(在用户定义的坐标系下)        |
| 24-27  | roll       |           | float32  | 相机绕x轴转动角度(在用户定义的坐标系下)  |
| 28-31  | pitch      |           | float32  | 相机绕y轴转动角度(在用户定义的坐标系下)  |
| 32-35  | yaw        |           | float32  | 相机绕z轴转动角度(在用户定义的坐标系下)  |
| 36-41  | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

response

| 字节    | Field      | sub-Field | 数据类型 | 数据                                     |
| ------- | ---------- | --------- | -------- | ---------------------------------------- |
| 0 – 3   | start_seq  |           | uint8[4] | (115, 116, 97, 114)即("star")            |
| 4 – 7   | command_id |           | uint32   | 11                                       |
| 8 – 11  | status     |           | int32    | 0或其他错误                              |
| 12 – 15 | len        |           | uint32   | 6                                        |
| 16-21   | seq_end    |           | uint8[6] | (115, 116, 111, 112, 13, 10)即"stop\n\r" |

## 附录

### 像素类型(pixel type)

| 代号 | 字节数 | OpenCV名 | c++数据类型   |
| ---- | ------ | -------- | ------------- |
| 0    | 1      | CV_8U    | std::uint8_t  |
| 1    | 1      | CV_8S    | std::int8_t   |
| 2    | 2      | CV_16U   | std::uint16_t |
| 3    | 2      | CV_16S   | std::int16_t  |
| 4    | 4      | CV_32S   | std::int32_t  |
| 5    | 4      | CV_32F   | float         |
| 6    | 8      | CV_64F   | double        |

### 数组ID

| 代号 | 名字                    | 描述                                                         |
| ---- | ----------------------- | ------------------------------------------------------------ |
| 0    | PCLOUD                  | Raw cartesian data from the sensor (float32, meters)         |
| 1    | IMD                     | Projection of the point cloud as a depth map – discretized to cm  resolution. Data are float32. |
| 2    | POCKS                   | A kx2 array of float32. K is the number of pockets detected and  each row is a detected pocket’s CG in pixels. This is the initial list  of candidate pockets segmented from the image. |
| 3    | PVALS                   | A k-element array of float32. Each value is the associated pocket’s  (in POCKS) correlation score. |
| 4    | IMBIN                   | A float32 array representing the binary depth image that is cross  correlated with the depth template to produce IMPOCK_RAW |
| 5    | IMPOCK_RAW              | A float32 array of the same dimension as IMD. This represents the  raw xcorr scores of IMD with the idealized pocket kernel. |
| 6    | KMAXES_IM               | A float32 array of the same dimension as IMPOCK_RAW. It  represents the filtered xcorr response paired down to the k-maxes  after applying the user-defined blanking neighborhood around the  maxes |
| 7    | RESERVED                |                                                              |
| 8    | RESERVED                |                                                              |
| 9    | RESERVED                |                                                              |
| 10   | PALLET                  | A 2x2 array (float32) of the form ‘[[xleft, yleft],[xright,yright]]’  which are the pocket CGs |
| 11   | PCONF                   | This is a 3x1 array encoding the pallet, left pocket, and right pocket confidence scores respectively. |
| 12   | FRAMED_POINTS           | The Cartesian coords of the frame points used to estimate the pallet  pose. This is a 3xk array where row0 = x, row1 = y, row2 = z.  These are in the camera frame |
| 13   | POSE                    | The 6-DOF pose of the pallet as a 12x1 column vector: [x y z xl yl  zl xr yr zr r p y].T Units are meters and radians. |
| 14   | TMPL                    | Full pocket correlation kernel                               |
| 15   | TMPL_HALF               | Half pocket correlation kernel                               |
| 16   | IS_WRAPPED              | K-element array of uint8 encoding the wrapped (1) or unwrapped  (0) state of a given pocket |
| 17   | IMPOCK_HALF_RAW         | A float32 array of the same dimension as IMD. This represents the  raw xcorr scores of IMD with the half-pocket kernel |
| 18   | KMAXES_HALF_IM          | Half-pocket version of KMAXES_IM                             |
| 19   | RESERVED                |                                                              |
| 20   | PWRAPPED                | 2x1 array denoting the wrapped (1) or unwrapped (0) state of the  pockets which make up the PALLET |
| 21   | GUID                    | An array of bytes representing a globally unique identifier for  “this” instance of the PDS. |
| 22   | REFERENCE_FORKS         | A kx3 point cloud of float32 representing the reference forks image used to check if the camera has been knocked out of calibration. |
| 23   | CALIB_CHECK             | The transform from the ‘live’ to the ‘reference’ forks (pose of the  reference forks in the live fork frame). Return is a 6-DOF pose [x y  z r p y] |
| 24   | RACK_CLOUD_CLEAN        | The denoised point cloud fed to the rack detection pipeline  |
| 25   | RACK_CLOUD_CHOPPED      | The clean rack detection point cloud chopped based on the depth  hint |
| 26   | RACK_BEAM               | The points on the rack beam face                             |
| 27   | RACK_BEAM_EDGE          | The points on the top-edge of the beam                       |
| 28   | RACK_NEAR_BEAM          | The point cloud chopped based on the segmented beam. This is the  cloud that is searched for the upright |
| 29   | RACK_UPRIGHT            | Points on the upright face                                   |
| 30   | RACK_UPRIGHT_EDGE       | Points on the interior edge of the upright                   |
| 31   | RACK_POBST              | Obstacle cloud                                               |
| 32   | RACK_FLOOR              | Floor points                                                 |
| 33   | RACK_SHELF_LIMITS       | Obstacle sweeping volume (in rack frame)                     |
| 34   | STRAY_LIGHT_CLOUD       | The points flagged as stray light pixels                     |
| 35   | AMPLITUDE               | Amplitude image                                              |
| 36   | DEPTH_HINT_SEED_PTS     | Point cloud showing seed points for auto-generated depth hint |
| 37   | PALLET_PTS_CLEAN        | Cleaned up point cloud fed to the v2 pallet detector         |
| 38   | IMBIN_FILT              | Median-filtered y-z projection of the point cloud (pallet pipeline) |
| 39   | IMLTOP                  | Xcorr response for left-top corners                          |
| 40   | IMLBOT                  | Xcorr response for left-bottom corners                       |
| 41   | IMRTOP                  | Xcorr response for right-top corners                         |
| 42   | IMRBOT                  | Xcorr response for right-bottom corners                      |
| 43   | TMPL_LTOP               | Xcorr kernel for left-top corners                            |
| 44   | TMPL_LBOT               | Xcorr kernel for left-bottom corners                         |
| 45   | TMPL_RTOP               | Xcorr kernel for right-top corners                           |
| 46   | TMPL_RBOT               | Xcorr kernel for right-bottom corners                        |
| 47   | IMLTOP_K                | Kmaxes image for left-top corners                            |
| 48   | IMLBOT_K                | Kmaxes image for left-bottom corners                         |
| 49   | IMRTOP_K                | Kmaxes image for right-top corners                           |
| 50   | IMRBOT_K                | Kmaxes image for right-bottom corners                        |
| 51   | LSIDES                  | (row,col) coords of the left sides of the pocket candidates  |
| 52   | RSIDES                  | (row,col) coords of the right sides of the pocket candidates |
| 53   | POCKS_V                 | Kx4 array of validated pockets [lrow lcol rrow rcol]         |
| 54   | POCKS_TOPS              | Kx4 array of pocket tops [LtopRow Lcol RbotRow Rcol] – used for testing occupancy along top of pocket frame. |
| 55   | VOL_CHECK_OBST          | Point cloud representing obstacle points in the block stacking VOI |
| 56   | STRAY_LIGHT_IDXS        | Binary map, registered to the imager array, showing pixels flagged  as stray light. |
| 57   | FFP_VMASK               | Mask denoting the pixels with the volume of interest of the  detection. |
| 58   | FFP_GAP_MASK            | Mask denoting areas of image saturation that will be excluded from ffp calculations to prevent skewed global statistics. |
| 59   | FFP_DIST_MASK           | Mask denoting outlier pixels flagged by the “distance-to-centroid”  metric applied by the ffp |
| 60   | FFP_FILT_MASK           | Mask denoting all outlier pixels flagged by the ffp          |
| 61   | FFP_KERNEL              | Convolution kernel used by ffp to compute the patch mean wrt an  anchor pixel. |
| 62   | FFP_DISTANCES           | The ffp-computed distances to the neighborhood centroid for each  anchor pixel in the array. |
| 63   | FFP_SIGMA_MASK          | Mask denoting outlier pixels flagged by the patch stddev metric  applied by the ffp. |
| 64   | LSIDE_CORNERS           | Coords (row,col) of corners used for constructing candidate left  sides in image space. |
| 65   | RSIDE_CORNERS           | Coords (row,col) of corners used for constructing candidate right  sides in image space. |
| 66   | POCK_DIMS_V             | Minimum dimensions (row,col) of all candidate pockets in image  space. |
| 67   | PALLET_POCKS            | Pocket coords and dimensions for the chosen pallet in image space  [llrow,llcol,lrrow,lrcol,lh,lw,rlrow,rlcol,rrrow,rrcol,rh,rw]. |
| 68   | POCKET_DIMENSIONS       | Minimum dimensions (lh, lw, rh, rw) of pockets for the chosen  pallet (meters). |
| 69   | PIPELINE_VERSION        | Version (Major, Minor, Patch) of the current PDS pipeline.   |
| 70   | HINTS                   | The returned `hints` array is command specific. However, in all  cases it reflects the hints passed in as part of the detection request.  All values are represented as float32. The array is encoded as  follows on a per command basis:CMD_VOL_CHECK: [0] – command id [1] – xmin [2] – xmax [3] – ymin [4] – ymax [5] – zmin [6] – zmax [7] – stray light filter flag                    CMD_GET_PALLET: [0] – command id [1] - pallet type [2] – depth hint [3] – filter mask                                                                                                                   CMD_GET_RACK: [0] – command id [1] – horizontal rack position [2] – vertical rack location [3] – camera position [4] – depth hint [5] – z hint [6] – clearing depth [7] – clearing width [8] – clearing height |
| 71   | RACK_BEAM_EDGE_MODEL    | A best fit 3D linear model to the points on the top edge of the  segmented rack beam. The array is a 6x1 column vector of float32:  [ux, uy, uz, px, py, pz].T Where `u` is a normalized vector colinear  to the line and `p` is a point on the line. |
| 72   | RACK_UPRIGHT_EDGE_MODEL | A best fit 3D linear model to the points on the interior edge of the  segmented rack upright. The array is a 6x1 column vector of  float32: [ux, uy, uz, px, py, pz].T Where `u` is a normalized vector  colinear to the line and `p` is a point on the line. |
| 73   | SW_SYNTH_SAT_CLOUD      | The points synthesized to ‘fill in’ saturation in the stretch wrap  filter |
| 74   | SW_SYNTH_SAT_IDXS       | The indexes of points (on the imager) that were synthesized by the  stretch wrap filter |
| 75   | SW_IM_XY_HIST           | The top-down (xy) 2D histogram used by the stretch wrap filter |
| 76   | SW_FILT_CLOUD           | The points removed by the stretch wrap filter                |
| 77   | SW_FILT_MASK            | The indexes of points (on the imager) removed by the stretch wrap  filter |
| 78   | EXTRINSICS              | The extrinsic information that has been saved to the device. The  array is a 6x1 column vector of float32: [x, y, z, roll, pitch, yaw]. If  extrinsics have not been saved, this returns an array of zeros. |

