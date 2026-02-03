# Usage

## setUsage

```cpp
void setUsage(const char* usage);
```

Set the usage message.

## getUsage

```cpp
std::string getUsage() const;
```

Get the usage message.

## setDescription

```cpp
void setDescription(const char* description);
```

Set the description in usage message.

## getDescription

```cpp
const std::string& getDescription() const;
```

Get the description message.

## setEpilog

```cpp
void setEpilog(const char* epilog);
```

Set the epilog in usage message.

## getEpilog

```cpp
const std::string& getEpilog() const;
```

Get the epilog message.

## setUsageWidth

```cpp
void setUsageWidth(std::size_t padWidth, std::size_t argsWidth, std::size_t sepWidth, std::size_t helpWidth);
```

Set the usage widths.

<img src="images/headerUsageWidth.drawio.png" />

```cpp
args.setUsageWidth(2, 20, 2, 56); // default
```

<img src="images/example1UsageWidth.drawio.png" />

```cpp
args.setUsageWidth(2, 30, 2, 15);
```

<img src="images/example2UsageWidth.drawio.png" />

```cpp
args.setUsageWidth(1, 21, 1, 30);
```

<img src="images/example3UsageWidth.drawio.png" />