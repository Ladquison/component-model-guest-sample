namespace UtilityWorld.wit.Exports.app.utility;

public class InfoExportsImpl : IInfoExports
{
    public static string GetMessage(int number)
    {
        return $"This is C# function, number = {number}";
    }
}
