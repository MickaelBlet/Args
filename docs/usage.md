# Usage

## setUsage

```cpp
void setUsage(const char* usage);
```

## getUsage

```cpp
std::string getUsage() const;
```

## setDescription

```cpp
void setDescription(const char* description);
```

## setEpilog

```cpp
void setEpilog(const char* epilog);
```

## setUsageWidth

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